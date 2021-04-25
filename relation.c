#include "relation.h"


#include <stdio.h>
#include <time.h>

#include "data_writer.h"
#include "enumerator.h"
#include "polymeric_enumerator.h"

address_t address_of(name_t relation)
{
	return relation == 'R' ? 1 : 17;
}

size_t length_of(name_t relation)
{
	return relation == 'R' ? 16 : 32;
}

void sort_each_block(name_t rel, name_t key, buffer_t buf)
{
	address_t next = address_of(rel);
	const size_t rel_length = length_of(rel);
	for (size_t i = 0; i < rel_length; i++)
	{
		//next = sort_block(next, key, buf);
	}
}

void linear_search(const name_t rel, const name_t key, const data_t value, buffer_t buf)
{
	printf(LONG_LINE);
	printf(CWL_RED"基于线性搜索的选择算法 %c.%c=%u:\n"CWL_NONE, rel, key, value);
	printf(LONG_LINE);
	address_t next = address_of(rel);
	data_writer_origin_t writer_base;
	data_writer_t writer = create_data_writer(&writer_base, URSQL_LINEAR_SEARCH_BASE, buf);

	size_t ans_count = 0;
	const size_t rel_length = length_of(rel);
	block_t* output = create_block(buf);
	for (size_t i = 0; i < rel_length; i++)
	{
		block_t* origin = load_block(next, buf);
		for (size_t i = 0; i < 7; i++)
		{
			const item_t current_item = origin->items[i];
			if (key_of(current_item, key) == value)
			{
				printf("(%d,%d)\n", current_item.first, current_item.second);
				ans_count++;
				append_data(writer, current_item);

			}
		}
		next = origin->next;
		free_block(origin, buf);
	}

	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	close_data_writer(writer);
	printf("\n");
	printf(CWL_RED"满足选择条件的元组一共%llu个。\n"CWL_NONE, ans_count);
	printf("\n");
	comment_io_times(buf);
	buf->numIO = 0;
}

void block_sort(name_t rel, name_t key, buffer_t buf)
{
	size_t block_sum_count = length_of(rel);
	address_t base_address = address_of(rel);
	block_t* blocks[8];
	while (block_sum_count)
	{
		const size_t load_size = min(block_sum_count, 8);
		block_sum_count -= load_size;
		//读入数据
		for (size_t i = 0; i < load_size; i++)
		{
			blocks[i] = load_block(base_address + i, buf);
		}
		//内排序
		sort_blocks(load_size, key, blocks);
		//导出数据
		for (size_t i = 0; i < load_size; i++)
		{
			blocks[i]->next = i + 1 == load_size ? 0 : URSQL_BLOCK_SORTED_BASE + base_address + i + 1;
			save_block(blocks[i], URSQL_BLOCK_SORTED_BASE + base_address + i, buf);
		}
		base_address += load_size;
	}
}

void tpmms(name_t rel, name_t key, buffer_t buf)
{
	printf(LONG_LINE);
	printf(CWL_RED"ORDER BY %c.%c:\n"CWL_NONE, rel, key);
	printf(LONG_LINE);

	// 第一段：分别排序
	block_sort(rel, key, buf);
	// 第二段：多路归并
	size_t block_sum_count = length_of(rel);
	address_t base_address = address_of(rel);
	// (至多)七路读取
	enumerator_origin_t enumerator_bases[7];
	enumerator_t enumerators[7];

	// 一路写入
	data_writer_origin_t writer_base;
	data_writer_t writer = create_data_writer(&writer_base, URSQL_ALL_SORTED_BASE + base_address, buf);
	//打开输入流
	size_t input_count = 0;
	while (block_sum_count)
	{
		const size_t load_size = min(block_sum_count, 8);
		block_sum_count -= load_size;
		enumerators[input_count]
			= initialize_enumerator(enumerator_bases + input_count, URSQL_BLOCK_SORTED_BASE + base_address, buf);
		input_count++;
		base_address += load_size;
	}
	// 聚合枚举器
	polymeric_enumerator_origin_t reader_base = { enumerators,input_count,min_of_enumerators,key,~0u };
	polymeric_enumerator_t reader = initialize_polymeric_enumerator(&reader_base);
	// 使用聚合枚举器排序
	do
	{
		append_data(writer, *value_of_polymeric(reader));
		move_next_polymeric(reader);
	} while (has_next_polymeric(reader));
	destroy_polymeric_enumerator(reader);
	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	// 关闭流
	close_data_writer(writer);
	printf("\n");
	comment_io_times(buf);
	buf->numIO = 0;

}

void create_index(name_t rel, property_info_t key, buffer_t buf)
{
	printf(LONG_LINE);
	printf(CWL_RED"建立索引 %c.%c:\n"CWL_NONE, rel, key.property_name);
	printf(LONG_LINE);
	// 假定排序已经完成
	data_writer_origin_t writer_base;
	data_writer_t writer = create_data_writer(&writer_base, address_of(rel) + URSQL_INDEX_BASE, buf);
	enumerator_origin_t origin_base;
	enumerator_t origin = initialize_enumerator(&origin_base, address_of(rel) + URSQL_ALL_SORTED_BASE, buf);

	data_t last = ~0u;

	do
	{
		data_t const value = key_of_pointer(value_of(origin), key.property_name);
		if (last != value)
		{
			item_t const data = { value,(data_t)origin->current_address };
			append_data(writer, data);
			last = value;
		}
		move_next(origin);
	} while (has_next(origin));

	destroy_enumerator(origin);
	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	// 关闭流
	close_data_writer(writer);
	printf("\n");
	comment_io_times(buf);
	buf->numIO = 0;

}

void inner_join(name_t this_rel, name_t target_rel, property_info_t inner_key, property_info_t outer_key, buffer_t buf)
{
	printf(LONG_LINE);
	printf(CWL_RED"基于排序的连接操作算法\n INNER JOIN %c\n ON%c.%c=%c.%c:\n"CWL_NONE,
		target_rel, this_rel, inner_key.property_name, target_rel, outer_key.property_name);
	printf(LONG_LINE);
	printf("分组排序...");
	block_sort(this_rel, inner_key.property_name, buf);
	block_sort(target_rel, outer_key.property_name, buf);
	printf("连接...");

	// (至多)七路读取
	enumerator_origin_t enumerator_bases[7];
	enumerator_t this_enumerators[7];
	// 一路写入
	data_writer_origin_t writer_base;
	data_writer_t writer = create_data_writer(&writer_base, URSQL_INNER_JOIN_BASE + address_of(this_rel), buf);
	//打开输入流
	size_t this_input_count = 0;
	size_t block_sum_count = length_of(this_rel);
	address_t base_address = address_of(this_rel);
	while (block_sum_count)
	{
		const size_t load_size = min(block_sum_count, 8);
		block_sum_count -= load_size;
		this_enumerators[this_input_count]
			= initialize_enumerator(enumerator_bases + this_input_count, URSQL_BLOCK_SORTED_BASE + base_address, buf);
		this_input_count++;
		base_address += load_size;
	}
	// 目标关系迭代器首
	enumerator_t* that_enumerators = this_enumerators + this_input_count;
	block_sum_count = length_of(target_rel);
	base_address = address_of(target_rel);
	size_t that_input_count = 0;
	while (block_sum_count)
	{
		const size_t load_size = min(block_sum_count, 8);
		block_sum_count -= load_size;
		that_enumerators[that_input_count]
			= initialize_enumerator(enumerator_bases + this_input_count + that_input_count,
				URSQL_BLOCK_SORTED_BASE + base_address, buf);
		that_input_count++;
		base_address += load_size;
	}
	// 连接
	while (that_input_count > 0 && that_input_count > 0)
	{
		for (size_t i = 0; i < this_input_count; i++)
		{
			/*if (key_of_pointer(value_of(this_enumerators[i]), inner_key.property_name)
				< outer_key.property_range.left)
			{
				if (has_next(this_enumerators[i]))
			}*/
		}
	}

	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	// 关闭流
	close_data_writer(writer);
	printf("\n");
	comment_io_times(buf);
	buf->numIO = 0;
}

void indexed_search(name_t rel, property_info_t key, const data_t value, buffer_t buf)
{
	printf(LONG_LINE);
	printf(CWL_RED"基于索引的选择算法 %c.%c=%u:\n"CWL_NONE, rel, key.property_name, value);
	printf(LONG_LINE);
	size_t offset = value - key.property_range.left;
	size_t ans_count = 0;
	address_t index_addr = address_of(rel) + URSQL_INDEX_BASE + offset / 7;
	block_t* index_block = load_block(index_addr, buf);
	address_t data_addr = index_block->items[offset % 7].second;
	free_block(index_block, buf);
	enumerator_origin_t origin_base;
	enumerator_t origin = initialize_enumerator(&origin_base, data_addr, buf);
	data_writer_origin_t writer_base;
	data_writer_t writer = create_data_writer(&writer_base, address_of(rel) + URSQL_INDEX_SEARCH_BASE, buf);
	do
	{
		item_t* const current_item = value_of(origin);
		data_t const current_value = key_of_pointer(current_item, key.property_name);

		if (current_value == value)
		{
			printf("(%d,%d)\n", current_item->first, current_item->second);
			ans_count++;
			append_data(writer, *current_item);
		}
		else if (ans_count)
		{
			break;
		}
		move_next(origin);
	} while (has_next(origin));
	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	// 关闭流
	close_data_writer(writer);
	destroy_enumerator(origin);
	printf("\n");
	printf(CWL_RED"满足选择条件的元组一共%llu个。\n"CWL_NONE, ans_count);
	printf("\n");
	comment_io_times(buf);
	buf->numIO = 0;
}

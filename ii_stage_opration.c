#include "ii_stage_opration.h"
#include <stdio.h>
#include "block.h"
#include "data_writer.h"
#include "polymeric_enumerator.h"
#include "ursql_io.h"

size_t ii_stage_operation(name_t this_rel, name_t that_rel,
	property_info_t this_main_key, property_info_t that_main_key,
	alg_stage_ii stage_ii, address_t ans_base_addr,
	buffer_t buf)
{
	printf("阶段I分组排序...\n");
	block_sort(this_rel, this_main_key.property_name, buf);
	block_sort(that_rel, that_main_key.property_name, buf);
	printf("阶段II归并操作...\n");

	// (至多)七路读取
	enumerator_origin_t enumerator_bases[7];
	enumerator_t this_enumerators[7];
	// 一路写入
	data_writer_origin_t writer_base;
	data_writer_t writer = create_data_writer(&writer_base, ans_base_addr, buf);
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
	block_sum_count = length_of(that_rel);
	base_address = address_of(that_rel);
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
	polymeric_enumerator_origin_t
		this_reader_base = { this_enumerators,this_input_count,min_of_enumerators,this_main_key.property_name,~0u },
		that_reader_base = { that_enumerators,that_input_count,min_of_enumerators,that_main_key.property_name,~0u };
	polymeric_enumerator_t
		this_reader = initialize_polymeric_enumerator(&this_reader_base),
		that_reader = initialize_polymeric_enumerator(&that_reader_base);



	size_t ans_count = stage_ii(writer, this_reader, that_reader, this_main_key, that_main_key, buf);
	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	// 关闭流
	close_data_writer(writer);
	destroy_polymeric_enumerator(this_reader);
	destroy_polymeric_enumerator(that_reader);
	printf("\n");
	return ans_count;
}

size_t inner_join_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
	property_info_t this_main_key, property_info_t that_main_key, buffer_t buf)
{
	size_t ans_count = 0;
	range_t ok_range = { max(this_main_key.property_range.left,that_main_key.property_range.left),
min(this_main_key.property_range.right,that_main_key.property_range.right) };
	data_t last_this_key = ~0u;
	bool have_any = false;
	for (;;)
	{
		item_t* this_value = value_of_polymeric(this_reader);
		data_t const this_key = key_of(this_value, this_main_key.property_name);
		if (this_key > ok_range.right) break;
		if (this_key >= ok_range.left)
		{
			if (last_this_key != this_key)
			{
				//开始缓存
				have_any = false;
				//挂起一个内关系的枚举器，以便转录
				suspend_enumerator(this_reader->enumerators[0]);
				//转录写入器
				data_writer_origin_t buffer_writer_base;
				data_writer_t buffer_writer = create_data_writer(&buffer_writer_base, URSQL_INNER_JOIN_BUFFER_BASE, buf);
				for (;;)
				{
					item_t* that_value = value_of_polymeric(that_reader);
					data_t const that_key = key_of(that_value, that_main_key.property_name);
					if (that_key > this_key) break;
					if (that_key == this_key) {
						have_any = true;
						append_data(buffer_writer, *that_value);
					}
					if (!has_next_polymeric(that_reader))break;
					move_next_polymeric(that_reader);
				}
				close_data_writer(buffer_writer);
				//挂起重启内关系的枚举器
				restart_enumerator(this_reader->enumerators[0]);
				last_this_key = this_key;
			}
			// 导入缓存
			if (have_any)
			{
				//挂起一个外关系的枚举器，以便转录
				suspend_enumerator(that_reader->enumerators[0]);
				//转录写入器
				enumerator_origin_t buffer_reader_base;
				enumerator_t buffer_reader = initialize_enumerator(&buffer_reader_base, URSQL_INNER_JOIN_BUFFER_BASE, buf);
				for (;;)
				{
					item_t* that_value = value_of(buffer_reader);
					data_t const that_key = key_of(that_value, that_main_key.property_name);
					if (that_key != this_key) break;
					if (that_key == this_key) {
						ans_count++;
						append_data(writer, *this_value);
						append_data(writer, *that_value);
					}
					if (!has_next(buffer_reader))break;
					move_next(buffer_reader);
				}
				destroy_enumerator(buffer_reader);
				//重启外关系的枚举器
				restart_enumerator(that_reader->enumerators[0]);
				last_this_key = this_key;

			}
		}
		if (!has_next_polymeric(this_reader))break;
		move_next_polymeric(this_reader);
	}

	return ans_count;
}

item_t* step(polymeric_enumerator_t reader)
{

	if (has_next_polymeric(reader))
	{
		move_next_polymeric(reader);
		return value_of_polymeric(reader);
	}
	return NULL;
}

size_t union_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
	property_info_t this_main_key, property_info_t that_main_key, buffer_t buf)
{
	size_t ans_count = 0;
	item_t* left_val = value_of_polymeric(this_reader);
	item_t* right_val = value_of_polymeric(that_reader);
	for (; left_val || right_val; ans_count++)
	{
		//如果左边空, 或左边大，则右边前进
		if (!left_val ||
			(right_val && compare_items(left_val, right_val, this_main_key.property_name) > 0))
		{
			append_data(writer, *right_val);
			right_val = step(that_reader);
			continue;
		}
		//如果右边空，或右边大，则左边前进
		if (!right_val || compare_items(left_val, right_val, this_main_key.property_name) < 0)
		{
			append_data(writer, *left_val);
			left_val = step(this_reader);
			continue;
		}
		//两边等值，同时前进
		append_data(writer, *left_val);
		left_val = step(this_reader);
		right_val = step(that_reader);
	}
	return ans_count;
}

size_t intersect_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
	property_info_t this_main_key, property_info_t that_main_key, buffer_t buf)
{
	size_t ans_count = 0;
	item_t* left_val = value_of_polymeric(this_reader);
	item_t* right_val = value_of_polymeric(that_reader);
	for (; left_val && right_val; )
	{
		//或左边大，则右边前进
		if (compare_items(left_val, right_val, this_main_key.property_name) > 0)
		{
			right_val = step(that_reader);
			continue;
		}
		//或右边大，则左边前进
		if (compare_items(left_val, right_val, this_main_key.property_name) < 0)
		{
			left_val = step(this_reader);
			continue;
		}
		//两边等值，同时前进
		append_data(writer, *left_val);
		left_val = step(this_reader);
		right_val = step(that_reader);
		ans_count++;
	}
	return ans_count;
}

size_t subtract_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
	property_info_t this_main_key, property_info_t that_main_key, buffer_t buf)
{
	size_t ans_count = 0;
	item_t* left_val = value_of_polymeric(this_reader);
	item_t* right_val = value_of_polymeric(that_reader);
	for (; left_val; )
	{
		//如果左边空, 或左边大，则右边前进
		if (right_val && compare_items(left_val, right_val, this_main_key.property_name) > 0)
		{
			right_val = step(that_reader);
			continue;
		}
		//如果右边空，或右边大，则左边前进
		if (!right_val || compare_items(left_val, right_val, this_main_key.property_name) < 0)
		{
			append_data(writer, *left_val);
			left_val = step(this_reader);
			ans_count++;
			continue;
		}
		//两边等值，同时前进
		left_val = step(this_reader);
		right_val = step(that_reader);
	}
	return ans_count;
}

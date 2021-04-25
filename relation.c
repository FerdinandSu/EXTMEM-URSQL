#include "relation.h"


#include <stdio.h>
#include <time.h>

#include "data_writer.h"
#include "enumerator.h"

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
	printf(CWL_RED"��������������ѡ���㷨 %c.%c=%u:\n"CWL_NONE, rel, key, value);
	printf(LONG_LINE);
	address_t next = address_of(rel);

	data_writer_t writer = create_data_writer(URSQL_LINEAR_SEARCH_BASE, buf);

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
		printf("next:%llu", next);
		free_block(origin, buf);
	}

	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	close_data_writer(writer);
	printf("\n");
	printf(CWL_RED"����ѡ��������Ԫ��һ��%llu����\n"CWL_NONE, ans_count);
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
		//��������
		for (size_t i = 0; i < load_size; i++)
		{
			blocks[i] = load_block(base_address + i, buf);
		}
		//������
		sort_blocks(load_size, key, blocks);
		//��������
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
	
	// ��һ�Σ��ֱ�����
	block_sort(rel, key, buf);
	// �ڶ��Σ���·�鲢
	size_t block_sum_count = length_of(rel);
	address_t base_address = address_of(rel);
	// (����)��·��ȡ
	enumerator_t enumerators[7];
	// һ·д��
	data_writer_t writer = create_data_writer(URSQL_ALL_SORTED_BASE + base_address, buf);
	//��������
	size_t input_count = 0;
	while (block_sum_count)
	{
		const size_t load_size = min(block_sum_count, 8);
		block_sum_count -= load_size;
		enumerators[input_count++]
			= create_enumerator(URSQL_BLOCK_SORTED_BASE + base_address, buf);
		base_address += load_size;
	}
	// ����
	while (input_count)
	{
		data_t min_val = ~0u;
		size_t min_i = 7;
		for (size_t i = 0; i < input_count; i++)
		{
			const data_t this_key = key_of_pointer(value_of(enumerators[i]), key);
			if (this_key < min_val)
			{
				min_val = this_key;
				min_i = i;
			}
		}
		if(min_i==7)
		{
			printf("Sort Failed.");
			return;
		}
		// ��Сֵд�����
		append_data(writer, *value_of(enumerators[min_i]));
		// ���µ�����
		if(has_next(enumerators[min_i]))
		{
			move_next(enumerators[min_i]);
		}
		else
		{
			// �Ӷ����Ƴ�û��Ԫ�صĵ�����
			destroy_enumerator(enumerators[min_i]);
			if(min_i+1!= input_count)
			{
				enumerators[min_i] = enumerators[input_count - 1];
			}
			input_count--;
			
		}
	}
	comment_wrote_into_blocks(writer->initial_block, writer->current_block);
	printf("\n");
	comment_io_times(buf);
	
	// �ر���
	close_data_writer(writer);
	for (size_t i = 0; i < input_count; i++)
	{
		destroy_enumerator(enumerators[i]);
	}
}

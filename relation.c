#include "relation.h"


#include <stdio.h>
#include <time.h>
#include "block.h"

address_t address_of(name_t relation)
{
	return relation == 'R' ? 1 : 17;
}

void sort_each_block(name_t rel, name_t key, buffer_t buf)
{
	address_t next = address_of(rel);
	while (next)
	{
		next = sort_block(next, key, buf);
	}
}

void linear_search(const name_t rel, const name_t key, const data_t value, buffer_t buf)
{
	address_t next = address_of(rel);
	address_t const o_left = URSQL_LINEAR_SEARCH_BASE;
	address_t o_right = o_left;
	size_t ans_count = 0;
	while (next)
	{
		block_t* origin = load_block(next, buf);
		for (size_t i = 0; i < 7; i++)
		{
			const item_t current_item = origin->items[i];
			if (key_of(current_item, key) == value)
			{
				printf("(%d,%d)\n", current_item.first, current_item.second);
				ans_count++;
			}
		}
		next = origin->next;
	}
}

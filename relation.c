#include "relation.h"

#include <time.h>
#include "block.h"

static inline data_t get_random_data(property_info_t field_info)
{
	return rand() % (field_info.property_range.right - field_info.property_range.left) + field_info.property_range.left;
}

bool generate_relation_data(relation_t info, buffer_t buffer, ARRAY(property_info_t) fields)
{
	if (fields.length != 2)return false;

	srand((uint)time(NULL));

	for (size_t i = 0; i < info.size; i++) {
		const address_t address = address_of(info.name) + i;

		block_t* block = create_block(buffer);

		for (size_t j = 0; j < 7; j++) {
			block->items[j].first = get_random_data(fields.items[0]);
			block->items[j].second = get_random_data(fields.items[0]);
		}
		block->next = i + 1 == info.size ? 0 : address + 1;

		save_block(block, address, buffer);
	}
	return true;
}

address_t address_of(name_t relation)
{
	return (address_t)relation * URSQL_ADDR_BASE;
}

void sort_each_block(name_t rel, name_t key, buffer_t buf)
{
	address_t next = address_of(rel);
	while (next)
	{
		next = sort_block(next, key, buf);
	}
}

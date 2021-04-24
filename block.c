#include "block.h"

block_t* create_block(buffer_t buffer)
{
	block_t* r = (block_t*)getNewBlockInBuffer(buffer);
	memset(r, 0, sizeof(block_t));
	return r;
}

bool save_block(block_t* block, address_t address, buffer_t buffer)
{
	return !writeBlockToDisk((unsigned char*)block, address, buffer);
}

block_t* load_block(address_t address, buffer_t buffer)
{
	return (block_t*)readBlockFromDisk(address, buffer);
}

static inline data_t key_of(item_t item, name_t key)
{
	// A(65),C(67)则使用第一项
	return key & 1 ? item.first : item.second;
}

address_t sort_block(address_t addr, name_t key, buffer_t buffer)
{
	block_t* const block = load_block(addr, buffer);
	item_t* const start = block->items;  // NOLINT(clang-diagnostic-incompatible-pointer-types-discards-qualifiers)
	item_t* end = (item_t*)block->items + 6;  // NOLINT(clang-diagnostic-incompatible-pointer-types-discards-qualifiers, clang-diagnostic-cast-qual)
	/* Note: in assertions below, i and j are always inside original bound of array to sort. */
	while (end > start)
	{
		item_t* max = start;
		for (item_t* p = start + 1; p <= end; p++)
			if (key_of(*p, key) > key_of(*max, key))
				max = p;
		item_t const swap_buf = *end;
		*end = *max;
		*max = swap_buf;
		end--;
	}
	const address_t next_addr = block->next;
	save_block(block, addr, buffer);
	return next_addr;
}

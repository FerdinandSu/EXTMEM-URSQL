#include "enumerator.h"
#include <memory.h>
#include "block.h"

enumerator_t create_enumerator(address_t first_block, buffer_t buffer)
{
	enumerator_t const r = (enumerator_t)calloc(1, sizeof(enumerator_origin_t));
	r->buffer = buffer;
	r->block = load_block(first_block, buffer);
	return r;
}

bool has_next(enumerator_t this)
{
	if (!this->block)return false;
	if (this->index < 6)return true;
	if (this->block->next)return true;
	return false;
}

void move_next(enumerator_t this)
{
	//Promise: Has NExt
	if (this->index < 6)
	{
		this->index++;
		return;
	}
	address_t const next = this->block->next;
	free_block(this->block, this->buffer);
	this->block = load_block(next, this->buffer);
	this->index = 0;

}

item_t* value_of(enumerator_t this)
{
	return this->block->items + this->index;
}

void destroy_enumerator(enumerator_t this)
{
	free_block(this->block, this->buffer);
	free(this);
}

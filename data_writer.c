#include "data_writer.h"

#include "block.h"

data_writer_t create_data_writer(address_t first_block, buffer_t buffer)
{
	data_writer_t const r = (data_writer_t)calloc(1, sizeof(data_writer_origin_t));
	r->buffer = buffer;
	r->block = load_block(first_block, buffer);
	r->current_block = first_block;
	r->initial_block = first_block;
	return r;
}

void append_data(data_writer_t this, item_t data)
{
	if (this->index == 7)
	{
		this->block->next = this->current_block + 1;
		save_block(this->block, this->current_block, this->buffer);
		this->current_block++;
		this->index = 0;
		this->block = create_block(this->buffer);
	}
	this->block->items[this->index++] = data;
}

void close_data_writer(data_writer_t this)
{
	if (this->index > 0)
		save_block(this->block, this->current_block, this->buffer);
	free(this);
}

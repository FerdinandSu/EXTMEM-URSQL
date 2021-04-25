#include "polymeric_enumerator.h"

static polymeric_enumerator_t check_polymeric_enumerator(polymeric_enumerator_t const this)
{
	for (size_t i = 0; i < this->enumerator_count; i++)
	{
		if (!has_next(this->enumerators[i]))
		{
			if (i + 1 != this->enumerator_count)
			{
				destroy_enumerator(this->enumerators[i]);
				this->enumerators[i] = this->enumerators[this->enumerator_count - 1];
			}
			this->enumerator_count--;
		}
	}
}
static polymeric_enumerator_t update_selected(polymeric_enumerator_t const this)
{
	this->selected = this->aggregator(this->enumerator_count, this->enumerators, this->key);
}
polymeric_enumerator_t initialize_polymeric_enumerator(polymeric_enumerator_t const this)
{
	check_polymeric_enumerator(this);
	update_selected(this);
}

bool has_next_polymeric(polymeric_enumerator_t this)
{
	return this->enumerator_count > 1 || has_next(this->enumerators[0]);
}

void move_next_polymeric(polymeric_enumerator_t this)
{
	if (has_next(this->enumerators[this->selected]))
	{
		move_next(this->enumerators[this->selected]);
	}
	else
	{
		//销毁选中的枚举器
		destroy_enumerator(this->enumerators[this->selected]);
		if (this->selected + 1 != this->enumerator_count)
		{
			this->enumerators[this->selected] = this->enumerators[this->enumerator_count - 1];
		}
		this->enumerator_count--;
	}
	update_selected(this);
}

item_t* value_of_polymeric(polymeric_enumerator_t this)
{
	return value_of(this->enumerators[this->selected]);
}

void destroy_polymeric_enumerator(polymeric_enumerator_t this)
{
	for (size_t i = 0; i < this->enumerator_count; i++)
	{
		destroy_enumerator(this->enumerators[i]);
	}
	this->selected = ~0u;
	this->enumerator_count = 0;
}

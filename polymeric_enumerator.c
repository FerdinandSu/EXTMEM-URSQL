#include "polymeric_enumerator.h"

static polymeric_enumerator_t check_polymeric_enumerator(polymeric_enumerator_t const this)
{
	for (size_t i = 0; i < this->enumerator_count; i++)
	{
		if (!has_next(this->enumerators[i]))
		{
			if (i + 1 != this->enumerator_count)
			{
				this->enumerators[i] = this->enumerators[this->enumerator_count - 1];
			}
			this->enumerator_count--;
		}
	}
}

polymeric_enumerator_t initialize_polymeric_enumerator(polymeric_enumerator_t const this)
{
	check_polymeric_enumerator(this);
}

bool has_next_polymeric(polymeric_enumerator_t this)
{
	return this->enumerator_count > 0;
}

void move_next_polymeric(polymeric_enumerator_t this)
{
	this->selected = this->aggregator(&(this->enumerator_count), this->enumerators, this->key);
}

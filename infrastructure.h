#pragma once

typedef struct struct_range {
	int left;
	int right;
} range_t;

typedef unsigned int uint;
typedef unsigned char byte;

#define USE_ARRAY(T) typedef struct struct_array_##T{uint length; T* items;} array_##T;
#define ARRAY(T) array_##T

	


USE_ARRAY(range_t)

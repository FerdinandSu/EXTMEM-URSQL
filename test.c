#include <stdlib.h>
#include <stdio.h>
#include "extmem.h"
#include "ursql.h"

int main(int argc, char** argv)
{
	Buffer buf; /* A buffer */
	int i = 0;

	/* Initialize the buffer */
	if (!initBuffer(520, 64, &buf))
	{
		perror("Buffer Initialization Failed!\n");
		return -1;
	}

	buffer_t buffer = &buf;

	range_t const r_a_range = { 20,60 };
	property_info_t const r_a = { 'A',r_a_range };
	
	range_t const s_c_range = { 40,80 };
	property_info_t const s_c = { 'C',s_c_range };
	

	// 线性检索
	//linear_search('S', 'C', 50, &buf);
	//TPMMS
	//tpmms('R', 'A', buffer);
	//tpmms('S', 'C', buffer);

	// 创建索引


	//create_index('S', s_c, buffer);

	// 索引检索
	//indexed_search('S', s_c, 50, buffer);

	inner_join('R', 'S', r_a, s_c, buffer);

	return 0;
}


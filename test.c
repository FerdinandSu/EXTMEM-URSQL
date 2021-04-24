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

	/* Get a new block in the buffer */
	linear_search('S', 'C', 50, &buf);

	
	return 0;
}


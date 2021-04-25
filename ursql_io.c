#include "ursql_io.h"

#include <stdio.h>

void comment_wrote_into_blocks(address_t left, address_t right)
{
	if (left == right)
		printf("ע�����д����̿飺%lld\n", left);
	else
		printf("ע�����д����̿飺%lld-%lld\n", left, right);
}

void comment_io_times(buffer_t buffer)
{
	printf(CWL_RED"IO��дһ��%lu��", buffer->numIO);
	printf(CWL_NONE"��\n");
}

void comment_item(item_t item)
{
	printf("(%d,%d)\n", item.first, item.second);
}

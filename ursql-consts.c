#include "ursql-consts.h"

data_t key_of(item_t* item, name_t key)
{
	// A(65),C(67)��ʹ�õ�һ��
	return key & 1 ? item->first : item->second;
}

address_t address_of(name_t relation)
{
	return relation == 'R' ? 1 : 17;
}

size_t length_of(name_t relation)
{
	return relation == 'R' ? 16 : 32;
}

data_t secondary_key_of(item_t* item, name_t key)
{
	// A(65),C(67)��ʹ�õڶ���
	return key & 1 ? item->second : item->first;
}

int compare_items(item_t* left, item_t* right, name_t main_key)
{
	//�Ƚϵ�һ��
	if (key_of(left, main_key) > key_of(right, main_key))
		return 1;
	if (key_of(left, main_key) < key_of(right, main_key))
		return -1;
	//�Ƚϵڶ���
	if (secondary_key_of(left, main_key) > secondary_key_of(right, main_key))
		return 1;
	if (secondary_key_of(left, main_key) < secondary_key_of(right, main_key))
		return -1;
	return 0;
}

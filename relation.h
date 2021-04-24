#pragma once
#include "ursql-consts.h"
#include "block.h"
#include "ursql_io.h"

typedef struct relation_t_str
{
	name_t name;
	size_t size;
} relation_t;


/// <summary>
/// ��ȡָ����ϵ�ĵ�ַ
/// </summary>
/// <param name="relation">��ϵ����</param>
/// <returns>��ַ</returns>
address_t address_of(name_t relation);

/// <summary>
/// ��ȡָ����ϵ�Ĵ�С
/// </summary>
/// <param name="relation">��ϵ����</param>
/// <returns>��ַ</returns>
size_t length_of(name_t relation);

/// <summary>
/// ��һ����ϵ��ÿһ�����������
/// </summary>
/// <param name="rel">��ϵ��Ϣ</param>
/// <param name="key">�������õļ�</param>
/// <param name="buf"></param>
void sort_each_block(name_t rel, name_t key, buffer_t buf);
/// <summary>
/// ���Լ�����ϵ���ҵ�������������Ŀ��
/// </summary>
/// <param name="rel">Ҫ�����Ĺ�ϵ</param>
/// <param name="key">�����ļ�</param>
/// <param name="value">ֵ</param>
/// <param name="buf">������</param>
void linear_search(name_t rel, name_t key, data_t value, buffer_t buf);
/// <summary>
/// ��ָ����ϵTPMMS
/// </summary>
/// <param name="rel">��ϵ</param>
/// <param name="key">��</param>
/// <param name="buf">������</param>
void tpmms(name_t rel, name_t key, buffer_t buf);
/// <summary>
/// ��ָ����ϵ�ֿ�����
/// </summary>
/// <param name="rel">��ϵ</param>
/// <param name="key">��</param>
/// <param name="buf">������</param>
void block_sort(name_t rel, name_t key, buffer_t buf);

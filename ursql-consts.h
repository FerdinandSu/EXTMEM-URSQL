/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * ��������
 */

#pragma once
#include "extmem.h"
#include"infrastructure.h"
/// <summary>
/// (������������)������ָ��
/// </summary>
typedef Buffer* buffer_t;
/// <summary>
/// ��ϵ����
/// </summary>
typedef char name_t;

/// <summary>
/// ����
/// </summary>
typedef uint data_t;
/// <summary>
/// ��ַ
/// </summary>
typedef size_t address_t;

typedef struct struct_property_info_t
{
	name_t property_name;
	range_t property_range;
} property_info_t;

USE_ARRAY(property_info_t)

/// <summary>
/// ��ϵ�е�һ��Ԫ��
/// </summary>
typedef struct item_t_str
{
	data_t first;
	data_t second;
} item_t;
/// <summary>
/// һ�������
/// </summary>
typedef struct block_t_str
{
	item_t items[7];
	address_t next;
} block_t;

/// <summary>
/// �ϸ�Ƚ�������Ŀ
/// </summary>
/// <param name="left">��һ��</param>
/// <param name="right">�ڶ���</param>
/// <param name="main_key">�Ƚϵ�����</param>
/// <returns></returns>
int compare_items(item_t* left, item_t* right, name_t main_key);
/// <summary>
/// ��ȡָ�����ϵ�ֵ
/// </summary>
/// <param name="item">��Ŀ</param>
/// <param name="key">��</param>
/// <returns>ֵ</returns>
data_t key_of(item_t* item, name_t key);



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

#define URSQL_LINEAR_SEARCH_BASE (address_t)1e2
#define URSQL_BLOCK_SORTED_BASE (address_t)2e2
#define URSQL_ALL_SORTED_BASE (address_t)3e2

#define URSQL_INDEX_BASE (address_t)4e2
#define URSQL_INDEX_SEARCH_BASE (address_t)5e2

#define URSQL_INNER_JOIN_BASE (address_t)6e2
#define URSQL_INNER_JOIN_BUFFER_BASE (address_t)7e2


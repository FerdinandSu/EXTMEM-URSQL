#pragma once
#include "extmem.h"
#include<stdbool.h>
#include"infrastructure.h"
#include<memory.h>

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
typedef int data_t;
/// <summary>
/// ��ַ
/// </summary>
typedef size_t address_t;

typedef struct struct_property_info_t
{
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

typedef bool(*sel)(item_t) selector;

#define URSQL_ADDR_BASE (address_t)1e3

#pragma once
#include "extmem.h"
#include<stdbool.h>
#include"infrastructure.h"
#include<memory.h>

/// <summary>
/// (命名规则修正)缓冲区指针
/// </summary>
typedef Buffer* buffer_t;
/// <summary>
/// 关系名称
/// </summary>
typedef char name_t;

/// <summary>
/// 数据
/// </summary>
typedef uint data_t;
/// <summary>
/// 地址
/// </summary>
typedef size_t address_t;

typedef struct struct_property_info_t
{
	name_t property_name;
	range_t property_range;
} property_info_t;

USE_ARRAY(property_info_t)

/// <summary>
/// 关系中的一个元素
/// </summary>
typedef struct item_t_str
{
	data_t first;
	data_t second;
} item_t;
/// <summary>
/// 一个储存块
/// </summary>
typedef struct block_t_str
{
	item_t items[7];
	address_t next;
} block_t;

#define URSQL_LINEAR_SEARCH_BASE (address_t)1e2
#define URSQL_BLOCK_SORTED_BASE (address_t)2e2
#define URSQL_ALL_SORTED_BASE (address_t)3e2

#define URSQL_INDEX_BASE (address_t)4e2
#define URSQL_INDEX_SEARCH_BASE (address_t)5e2

#define URSQL_INNER_JOIN_BASE (address_t)6e2
#define URSQL_INNER_JOIN_BUFFER_BASE (address_t)7e2

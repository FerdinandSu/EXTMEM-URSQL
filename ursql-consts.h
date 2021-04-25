/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 常量定义
 */

#pragma once
#include "extmem.h"
#include"infrastructure.h"
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

/// <summary>
/// 严格比较两个项目
/// </summary>
/// <param name="left">第一项</param>
/// <param name="right">第二项</param>
/// <param name="main_key">比较的主键</param>
/// <returns></returns>
int compare_items(item_t* left, item_t* right, name_t main_key);
/// <summary>
/// 获取指定键上的值
/// </summary>
/// <param name="item">项目</param>
/// <param name="key">键</param>
/// <returns>值</returns>
data_t key_of(item_t* item, name_t key);



/// <summary>
/// 获取指定关系的地址
/// </summary>
/// <param name="relation">关系名称</param>
/// <returns>地址</returns>
address_t address_of(name_t relation);

/// <summary>
/// 获取指定关系的大小
/// </summary>
/// <param name="relation">关系名称</param>
/// <returns>地址</returns>
size_t length_of(name_t relation);

#define URSQL_LINEAR_SEARCH_BASE (address_t)1e2
#define URSQL_BLOCK_SORTED_BASE (address_t)2e2
#define URSQL_ALL_SORTED_BASE (address_t)3e2

#define URSQL_INDEX_BASE (address_t)4e2
#define URSQL_INDEX_SEARCH_BASE (address_t)5e2

#define URSQL_INNER_JOIN_BASE (address_t)6e2
#define URSQL_INNER_JOIN_BUFFER_BASE (address_t)7e2


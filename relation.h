#pragma once
#include "ursql-consts.h"

typedef struct relation_t_str
{
	name_t name;
	size_t size;
} relation_t;


/// <summary>
/// 获取指定关系的地址
/// </summary>
/// <param name="relation">关系名称</param>
/// <returns>地址</returns>
address_t address_of(name_t relation);

/// <summary>
/// 对一个关系的每一个储存块排序
/// </summary>
/// <param name="rel">关系信息</param>
/// <param name="key">排序所用的键</param>
/// <param name="buf"></param>
void sort_each_block(name_t rel, name_t key, buffer_t buf);
/// <summary>
/// 线性检索关系，找到满足条件的条目们
/// </summary>
/// <param name="rel">要检索的关系</param>
/// <param name="key">检索的键</param>
/// <param name="value">值</param>
/// <param name="buf">缓冲区</param>
void linear_search(name_t rel, name_t key, data_t value, buffer_t buf);

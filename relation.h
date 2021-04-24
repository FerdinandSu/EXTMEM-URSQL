#pragma once
#include "ursql-consts.h"

typedef struct relation_t_str
{
	name_t name;
	size_t size;
} relation_t;

/// <summary>
/// 尝试创建一个新的关系
/// </summary>
/// <param name="info">关系信息</param>
/// <param name="buffer">缓冲区</param>
/// <param name="fields">关系包含的字段</parm>
/// <returns>是否创建成功</returns>
bool generate_relation_data(
	relation_t info,
	buffer_t buffer,
	ARRAY(property_info_t) fields
);

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

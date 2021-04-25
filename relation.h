/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 关系操作
 */

#pragma once
#include "ursql-consts.h"

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
/// <summary>
/// 用索引检索关系，找到满足条件的条目们
/// </summary>
/// <param name="rel">要检索的关系</param>
/// <param name="key">检索的键</param>
/// <param name="value">值</param>
/// <param name="buf">缓冲区</param>
void indexed_search(name_t rel, property_info_t key, data_t value, buffer_t buf);
/// <summary>
/// 对指定关系TPMMS
/// </summary>
/// <param name="rel">关系</param>
/// <param name="key">键</param>
/// <param name="buf">缓冲区</param>
void tpmms(name_t rel, name_t key, buffer_t buf);

/// <summary>
/// 根据排序结果创建索引。创建索引的复杂度是O(n)的，但是理论上可以内联于排序。
/// </summary>
/// <param name="rel">关系</param>
/// <param name="key">键</param>
/// <param name="buf">缓冲区</param>
void create_index(name_t rel, property_info_t key, buffer_t buf);
/// <summary>
/// 内连接两个关系
/// </summary>
/// <param name="this_rel">主关系</param>
/// <param name="target_rel">被接入的关系</param>
/// <param name="inner_key">内键</param>
/// <param name="outer_key">外键</param>
/// <param name="buf">缓冲区</param>
void inner_join(name_t this_rel, name_t target_rel, property_info_t inner_key, property_info_t outer_key, buffer_t buf);

/// <summary>
/// 求两个关系的并集。两个集合被视为同质化的。
/// </summary>
/// <param name="this_rel">左集合</param>
/// <param name="target_rel">右集合</param>
/// <param name="inner_key">左集合主键</param>
/// <param name="outer_key">右集合主键</param>
/// <param name="buf">缓冲区</param>
void union_sets(name_t this_rel, name_t target_rel, property_info_t inner_key, property_info_t outer_key, buffer_t buf);

/// <summary>
/// 求两个关系的交集。两个集合被视为同质化的。
/// </summary>
/// <param name="this_rel">左集合</param>
/// <param name="target_rel">右集合</param>
/// <param name="inner_key">左集合主键</param>
/// <param name="outer_key">右集合主键</param>
/// <param name="buf">缓冲区</param>
void intersect_sets(name_t this_rel, name_t target_rel, property_info_t inner_key, property_info_t outer_key, buffer_t buf);

/// <summary>
/// 求两个关系的差集。两个集合被视为同质化的。
/// </summary>
/// <param name="this_rel">左集合</param>
/// <param name="target_rel">右集合</param>
/// <param name="inner_key">左集合主键</param>
/// <param name="outer_key">右集合主键</param>
/// <param name="buf">缓冲区</param>
void subtract_sets(name_t this_rel, name_t target_rel, property_info_t inner_key, property_info_t outer_key, buffer_t buf);

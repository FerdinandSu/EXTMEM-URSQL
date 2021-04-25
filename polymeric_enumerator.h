/**
 * polymeric_enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 聚合枚举器
 * 使用特定聚合器聚合一系列枚举器的序列
 */
#pragma once
#include "enumerator.h"
#include "ursql-consts.h"

 /// <summary>
 /// 聚合器
 /// </summary>
typedef enumerator_t* (*aggregator_t)(size_t*, enumerator_t*, name_t key);

/// <summary>
/// 聚合枚举器
/// </summary>
typedef struct polymeric_enumerator_str
{
	enumerator_t* enumerators;
	size_t enumerator_count;
	aggregator_t aggregator;
	name_t key;
	enumerator_t* selected;

} polymeric_enumerator_origin_t;
/// <summary>
/// 枚举器
/// </summary>
typedef polymeric_enumerator_origin_t* polymeric_enumerator_t;

/// <summary>
/// 使用给定的地址创建一个枚举器
/// </summary>
/// <param name="this">要初始化的枚举器</param>
/// <param name="first_block">第一块的地址</param>
/// <param name="buffer">缓冲区</param>
/// <returns>创建的枚举器</returns>
polymeric_enumerator_t initialize_polymeric_enumerator(polymeric_enumerator_t const this);
/// <summary>
/// 枚举器是否有下一个元素
/// </summary>
/// <param name="this">当前枚举器</param>
/// <returns>是否有下一个元素</returns>
bool has_next_polymeric(polymeric_enumerator_t  this);
/// <summary>
/// 枚举器移动到下一个元素
/// </summary>
/// <param name="this">当前枚举器</param>
void move_next_polymeric(polymeric_enumerator_t this);
/// <summary>
/// 枚举器当前元素
/// </summary>
/// <param name="this">当前枚举器</param>
/// <returns>当前元素</returns>
item_t* value_of_polymeric(polymeric_enumerator_t this);
/// <summary>
/// 释放是否有下一个元素
/// </summary>
/// <param name="this">当前枚举器</param>
void destroy_polymeric_enumerator(polymeric_enumerator_t this);

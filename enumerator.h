/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 枚举器
 */
#pragma once
#include "ursql-consts.h"

/// <summary>
/// 枚举器
/// </summary>
typedef struct enumerator_str
{
	buffer_t buffer;
	block_t* block;
	size_t index;
	address_t current_address;
} enumerator_origin_t;
/// <summary>
/// 枚举器
/// </summary>
typedef enumerator_origin_t* enumerator_t;

/// <summary>
/// 使用给定的地址创建一个枚举器
/// </summary>
/// <param name="this">要初始化的枚举器</param>
/// <param name="first_block">第一块的地址</param>
/// <param name="buffer">缓冲区</param>
/// <returns>创建的枚举器</returns>
enumerator_t initialize_enumerator(enumerator_t const this, address_t first_block, buffer_t buffer);
/// <summary>
/// 枚举器是否有下一个元素
/// </summary>
/// <param name="this">当前枚举器</param>
/// <returns>是否有下一个元素</returns>
bool has_next(enumerator_t  this);
/// <summary>
/// 枚举器移动到下一个元素
/// </summary>
/// <param name="this">当前枚举器</param>
void move_next(enumerator_t this);
/// <summary>
/// 枚举器当前元素
/// </summary>
/// <param name="this">当前枚举器</param>
/// <returns>当前元素</returns>
item_t* value_of(enumerator_t this);
/// <summary>
/// 释放枚举器
/// </summary>
/// <param name="this">当前枚举器</param>
void destroy_enumerator(enumerator_t this);

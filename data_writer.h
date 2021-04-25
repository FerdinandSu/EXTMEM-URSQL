/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 数据写入器，项目输出流
 */

#pragma once
#include "ursql-consts.h"

/// <summary>
/// 数据写入器
/// </summary>
typedef struct data_writer_str
{
	buffer_t buffer;
	block_t* block;
	size_t index;
	address_t initial_block;
	address_t current_block;
} data_writer_origin_t;
/// <summary>
/// 数据写入器
/// </summary>
typedef data_writer_origin_t* data_writer_t;

/// <summary>
/// 使用给定的地址创建一个数据写入器
/// </summary>
/// <param name="this">要初始化的写入器</param>
/// <param name="first_block">第一块的地址</param>
/// <param name="buffer">缓冲区</param>
/// <returns>创建的写入器</returns>
data_writer_t create_data_writer(data_writer_t this, address_t first_block, buffer_t buffer);

/// <summary>
/// 写入一个元素
/// </summary>
/// <param name="this">当前数据写入器</param>
void append_data(data_writer_t this, item_t data);

/// <summary>
/// 保存写入的内容
/// </summary>
/// <param name="this">当前数据写入器</param>
void close_data_writer(data_writer_t this);



/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 通用输入输出操作
 */

#pragma once
#include "ursql-consts.h"

/// <summary>
/// 输出磁盘块写入说明
/// </summary>
/// <param name="left">第一块</param>
/// <param name="right">最后一块</param>
void comment_wrote_into_blocks(address_t left, address_t right);

/// <summary>
/// 输出读写次数
/// </summary>
/// <param name="buffer">缓冲区</param>
void comment_io_times(buffer_t buffer);

/// <summary>
/// 输出一个项目
/// </summary>
/// <param name="item">要输出的项目</param>
void comment_item(item_t item);

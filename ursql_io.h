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
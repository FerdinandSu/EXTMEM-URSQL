#pragma once
#include "ursql-consts.h"

/// <summary>
/// 创建储存块
/// </summary>
/// <param name="buffer">缓冲区</param>
/// <returns>指向已创建块的指针</returns>
 block_t* create_block(buffer_t buffer);
/// <summary>
/// 释放储存块
/// </summary>
/// <param name="block">储存块</param>
/// <param name="buffer">缓冲区</param>
void free_block(block_t* block,buffer_t buffer);
/// <summary>
/// 保存一个块
/// </summary>
/// <param name="block">块指针</param>
/// <param name="address">地址</param>
/// <param name="buffer">缓冲区</param>
/// <returns></returns>
 bool save_block(block_t* block, address_t address, buffer_t buffer);
/// <summary>
/// 加载一个块
/// </summary>
/// <param name="address">地址</param>
/// <param name="buffer">缓冲区</param>
/// <returns>块指针</returns>
 block_t* load_block(address_t address, buffer_t buffer);
/// <summary>
/// 获取指定键上的值
/// </summary>
/// <param name="item">项目</param>
/// <param name="key">键</param>
/// <returns>值</returns>
 data_t key_of(item_t item, name_t key);
 /// <summary>
 /// 获取指定键上的值
 /// </summary>
 /// <param name="item">项目</param>
 /// <param name="key">键</param>
 /// <returns>值</returns>
 data_t key_of_pointer(item_t* item, name_t key);
/// <summary>
/// 对指定的块进行升序排序.
/// </summary>
/// <param name="block">块地址</param>
/// <param name="key">排序依据</param>
/// <return>下一块地址</return>
void sort_block(block_t* block, name_t key);
/// <summary>
/// 排序指定个数的块
/// </summary>
/// <param name="count">块数</param>
/// <param name="key">键</param>
/// <param name="blocks">块数组</param>
void sort_blocks(size_t count, name_t key, block_t** blocks);

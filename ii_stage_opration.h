/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * 两端扫描操作
 */

#pragma once
#include "data_writer.h"
#include "polymeric_enumerator.h"
#include "ursql-consts.h"

/// <summary>
/// 两端扫描算法的第二段
/// </summary>
typedef size_t(*alg_stage_ii)(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// 使用两个关系的两端扫描操作
/// </summary>
/// <param name="this_rel">关系1</param>
/// <param name="that_rel">关系2</param>
/// <param name="this_main_key">关系1主键</param>
/// <param name="that_main_key">关系2主键</param>
/// <param name="stage_ii">阶段二的操作</param>
/// <param name="ans_base_addr">输出文件基地址</param>
/// <param name="buf">缓冲区</param>
/// <returns>操作统计结果</returns>
size_t ii_stage_operation(
    name_t this_rel, name_t that_rel,
    property_info_t this_main_key, property_info_t that_main_key,
    alg_stage_ii stage_ii, address_t ans_base_addr,
    buffer_t buf);
/// <summary>
/// 内连接的第二阶段操作
/// </summary>
/// <param name="writer">输出</param>
/// <param name="this_reader">关系1输入</param>
/// <param name="that_reader">关系2输入</param>
/// <param name="this_main_key">关系1主键</param>
/// <param name="that_main_key">关系2主键</param>
/// <param name="buf">缓冲区</param>
/// <returns>操作结果</returns>
size_t inner_join_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// 并集的第二阶段操作
/// </summary>
/// <param name="writer">输出</param>
/// <param name="this_reader">关系1输入</param>
/// <param name="that_reader">关系2输入</param>
/// <param name="this_main_key">关系1主键</param>
/// <param name="that_main_key">关系2主键</param>
/// <param name="buf">缓冲区</param>
/// <returns>操作结果</returns>
size_t union_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// 交集的第二阶段操作
/// </summary>
/// <param name="writer">输出</param>
/// <param name="this_reader">关系1输入</param>
/// <param name="that_reader">关系2输入</param>
/// <param name="this_main_key">关系1主键</param>
/// <param name="that_main_key">关系2主键</param>
/// <param name="buf">缓冲区</param>
/// <returns>操作结果</returns>
size_t intersect_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// 差集的第二阶段操作
/// </summary>
/// <param name="writer">输出</param>
/// <param name="this_reader">关系1输入</param>
/// <param name="that_reader">关系2输入</param>
/// <param name="this_main_key">关系1主键</param>
/// <param name="that_main_key">关系2主键</param>
/// <param name="buf">缓冲区</param>
/// <returns>操作结果</returns>
size_t subtract_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

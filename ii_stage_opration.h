/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * ����ɨ�����
 */

#pragma once
#include "data_writer.h"
#include "polymeric_enumerator.h"
#include "ursql-consts.h"

/// <summary>
/// ����ɨ���㷨�ĵڶ���
/// </summary>
typedef size_t(*alg_stage_ii)(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// ʹ��������ϵ������ɨ�����
/// </summary>
/// <param name="this_rel">��ϵ1</param>
/// <param name="that_rel">��ϵ2</param>
/// <param name="this_main_key">��ϵ1����</param>
/// <param name="that_main_key">��ϵ2����</param>
/// <param name="stage_ii">�׶ζ��Ĳ���</param>
/// <param name="ans_base_addr">����ļ�����ַ</param>
/// <param name="buf">������</param>
/// <returns>����ͳ�ƽ��</returns>
size_t ii_stage_operation(
    name_t this_rel, name_t that_rel,
    property_info_t this_main_key, property_info_t that_main_key,
    alg_stage_ii stage_ii, address_t ans_base_addr,
    buffer_t buf);
/// <summary>
/// �����ӵĵڶ��׶β���
/// </summary>
/// <param name="writer">���</param>
/// <param name="this_reader">��ϵ1����</param>
/// <param name="that_reader">��ϵ2����</param>
/// <param name="this_main_key">��ϵ1����</param>
/// <param name="that_main_key">��ϵ2����</param>
/// <param name="buf">������</param>
/// <returns>�������</returns>
size_t inner_join_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// �����ĵڶ��׶β���
/// </summary>
/// <param name="writer">���</param>
/// <param name="this_reader">��ϵ1����</param>
/// <param name="that_reader">��ϵ2����</param>
/// <param name="this_main_key">��ϵ1����</param>
/// <param name="that_main_key">��ϵ2����</param>
/// <param name="buf">������</param>
/// <returns>�������</returns>
size_t union_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// �����ĵڶ��׶β���
/// </summary>
/// <param name="writer">���</param>
/// <param name="this_reader">��ϵ1����</param>
/// <param name="that_reader">��ϵ2����</param>
/// <param name="this_main_key">��ϵ1����</param>
/// <param name="that_main_key">��ϵ2����</param>
/// <param name="buf">������</param>
/// <returns>�������</returns>
size_t intersect_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

/// <summary>
/// ��ĵڶ��׶β���
/// </summary>
/// <param name="writer">���</param>
/// <param name="this_reader">��ϵ1����</param>
/// <param name="that_reader">��ϵ2����</param>
/// <param name="this_main_key">��ϵ1����</param>
/// <param name="that_main_key">��ϵ2����</param>
/// <param name="buf">������</param>
/// <returns>�������</returns>
size_t subtract_stage_ii(data_writer_t writer, polymeric_enumerator_t this_reader, polymeric_enumerator_t that_reader,
    property_info_t this_main_key, property_info_t that_main_key, buffer_t buf);

#pragma once
#include "ursql-consts.h"

/// <summary>
/// ���������
/// </summary>
/// <param name="buffer">������</param>
/// <returns>ָ���Ѵ������ָ��</returns>
inline block_t* create_block(buffer_t buffer);
/// <summary>
/// ����һ����
/// </summary>
/// <param name="block">��ָ��</param>
/// <param name="address">��ַ</param>
/// <param name="buffer">������</param>
/// <returns></returns>
inline bool save_block(block_t* block, address_t address, buffer_t buffer);
/// <summary>
/// ����һ����
/// </summary>
/// <param name="address">��ַ</param>
/// <param name="buffer">������</param>
/// <returns>��ָ��</returns>
inline block_t* load_block(address_t address, buffer_t buffer);
/// <summary>
/// ��ȡָ�����ϵ�ֵ
/// </summary>
/// <param name="item">��Ŀ</param>
/// <param name="key">��</param>
/// <returns>ֵ</returns>
static inline data_t key_of(item_t item, name_t key);
/// <summary>
/// ��ָ����ַ���Ŀ������������
/// </summary>
/// <param name="addr">���ַ</param>
/// <param name="key">��������</param>
/// <param name="buffer">������</param>
/// <return>��һ���ַ</return>
address_t sort_block(address_t addr, name_t key, buffer_t buffer);

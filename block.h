#pragma once
#include "ursql-consts.h"

/// <summary>
/// ���������
/// </summary>
/// <param name="buffer">������</param>
/// <returns>ָ���Ѵ������ָ��</returns>
 block_t* create_block(buffer_t buffer);
/// <summary>
/// �ͷŴ����
/// </summary>
/// <param name="block">�����</param>
/// <param name="buffer">������</param>
void free_block(block_t* block,buffer_t buffer);
/// <summary>
/// ����һ����
/// </summary>
/// <param name="block">��ָ��</param>
/// <param name="address">��ַ</param>
/// <param name="buffer">������</param>
/// <returns></returns>
 bool save_block(block_t* block, address_t address, buffer_t buffer);
/// <summary>
/// ����һ����
/// </summary>
/// <param name="address">��ַ</param>
/// <param name="buffer">������</param>
/// <returns>��ָ��</returns>
 block_t* load_block(address_t address, buffer_t buffer);
/// <summary>
/// ��ȡָ�����ϵ�ֵ
/// </summary>
/// <param name="item">��Ŀ</param>
/// <param name="key">��</param>
/// <returns>ֵ</returns>
 data_t key_of(item_t item, name_t key);
 /// <summary>
 /// ��ȡָ�����ϵ�ֵ
 /// </summary>
 /// <param name="item">��Ŀ</param>
 /// <param name="key">��</param>
 /// <returns>ֵ</returns>
 data_t key_of_pointer(item_t* item, name_t key);
/// <summary>
/// ��ָ���Ŀ������������.
/// </summary>
/// <param name="block">���ַ</param>
/// <param name="key">��������</param>
/// <return>��һ���ַ</return>
void sort_block(block_t* block, name_t key);
/// <summary>
/// ����ָ�������Ŀ�
/// </summary>
/// <param name="count">����</param>
/// <param name="key">��</param>
/// <param name="blocks">������</param>
void sort_blocks(size_t count, name_t key, block_t** blocks);

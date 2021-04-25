/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * ����д��������Ŀ�����
 */

#pragma once
#include "ursql-consts.h"

/// <summary>
/// ����д����
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
/// ����д����
/// </summary>
typedef data_writer_origin_t* data_writer_t;

/// <summary>
/// ʹ�ø����ĵ�ַ����һ������д����
/// </summary>
/// <param name="this">Ҫ��ʼ����д����</param>
/// <param name="first_block">��һ��ĵ�ַ</param>
/// <param name="buffer">������</param>
/// <returns>������д����</returns>
data_writer_t create_data_writer(data_writer_t this, address_t first_block, buffer_t buffer);

/// <summary>
/// д��һ��Ԫ��
/// </summary>
/// <param name="this">��ǰ����д����</param>
void append_data(data_writer_t this, item_t data);

/// <summary>
/// ����д�������
/// </summary>
/// <param name="this">��ǰ����д����</param>
void close_data_writer(data_writer_t this);



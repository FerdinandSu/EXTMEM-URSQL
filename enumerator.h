/**
 * enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * ö����
 */
#pragma once
#include "ursql-consts.h"

/// <summary>
/// ö����
/// </summary>
typedef struct enumerator_str
{
	buffer_t buffer;
	block_t* block;
	size_t index;
	address_t current_address;
} enumerator_origin_t;
/// <summary>
/// ö����
/// </summary>
typedef enumerator_origin_t* enumerator_t;

/// <summary>
/// ʹ�ø����ĵ�ַ����һ��ö����
/// </summary>
/// <param name="this">Ҫ��ʼ����ö����</param>
/// <param name="first_block">��һ��ĵ�ַ</param>
/// <param name="buffer">������</param>
/// <returns>������ö����</returns>
enumerator_t initialize_enumerator(enumerator_t const this, address_t first_block, buffer_t buffer);
/// <summary>
/// ö�����Ƿ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰö����</param>
/// <returns>�Ƿ�����һ��Ԫ��</returns>
bool has_next(enumerator_t  this);
/// <summary>
/// ö�����ƶ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰö����</param>
void move_next(enumerator_t this);
/// <summary>
/// ö������ǰԪ��
/// </summary>
/// <param name="this">��ǰö����</param>
/// <returns>��ǰԪ��</returns>
item_t* value_of(enumerator_t this);
/// <summary>
/// �ͷ�ö����
/// </summary>
/// <param name="this">��ǰö����</param>
void destroy_enumerator(enumerator_t this);

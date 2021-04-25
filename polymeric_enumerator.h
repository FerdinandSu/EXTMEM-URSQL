/**
 * polymeric_enumerator.h
 * Ferdinand Sukhoi
 * Harbin Institute of Technology
 * April 25, 2021
 *
 * �ۺ�ö����
 * ʹ���ض��ۺ����ۺ�һϵ��ö����������
 */
#pragma once
#include "enumerator.h"
#include "ursql-consts.h"

 /// <summary>
 /// �ۺ���
 /// </summary>
typedef enumerator_t* (*aggregator_t)(size_t*, enumerator_t*, name_t key);

/// <summary>
/// �ۺ�ö����
/// </summary>
typedef struct polymeric_enumerator_str
{
	enumerator_t* enumerators;
	size_t enumerator_count;
	aggregator_t aggregator;
	name_t key;
	enumerator_t* selected;

} polymeric_enumerator_origin_t;
/// <summary>
/// ö����
/// </summary>
typedef polymeric_enumerator_origin_t* polymeric_enumerator_t;

/// <summary>
/// ʹ�ø����ĵ�ַ����һ��ö����
/// </summary>
/// <param name="this">Ҫ��ʼ����ö����</param>
/// <param name="first_block">��һ��ĵ�ַ</param>
/// <param name="buffer">������</param>
/// <returns>������ö����</returns>
polymeric_enumerator_t initialize_polymeric_enumerator(polymeric_enumerator_t const this);
/// <summary>
/// ö�����Ƿ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰö����</param>
/// <returns>�Ƿ�����һ��Ԫ��</returns>
bool has_next_polymeric(polymeric_enumerator_t  this);
/// <summary>
/// ö�����ƶ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰö����</param>
void move_next_polymeric(polymeric_enumerator_t this);
/// <summary>
/// ö������ǰԪ��
/// </summary>
/// <param name="this">��ǰö����</param>
/// <returns>��ǰԪ��</returns>
item_t* value_of_polymeric(polymeric_enumerator_t this);
/// <summary>
/// �ͷ��Ƿ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰö����</param>
void destroy_polymeric_enumerator(polymeric_enumerator_t this);

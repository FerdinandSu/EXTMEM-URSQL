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
typedef size_t (*aggregator_t)(size_t, enumerator_t*, name_t key);

/// <summary>
/// �ۺ�ö����
/// </summary>
typedef struct polymeric_enumerator_str
{
	enumerator_t* enumerators;
	size_t enumerator_count;
	aggregator_t aggregator;
	name_t key;
	size_t selected;

} polymeric_enumerator_origin_t;
/// <summary>
/// �ۺ�ö����
/// </summary>
typedef polymeric_enumerator_origin_t* polymeric_enumerator_t;

/// <summary>
/// ʹ�ø����ĵ�ַ����һ���ۺ�ö����
/// </summary>
/// <param name="this">Ҫ��ʼ���ľۺ�ö����</param>
/// <returns>������ö����</returns>
polymeric_enumerator_t initialize_polymeric_enumerator(polymeric_enumerator_t this);
/// <summary>
/// �ۺ�ö�����Ƿ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰ�ۺ�ö����</param>
/// <returns>�Ƿ�����һ��Ԫ��</returns>
bool has_next_polymeric(polymeric_enumerator_t  this);
/// <summary>
/// �ۺ�ö�����ƶ�����һ��Ԫ��
/// </summary>
/// <param name="this">��ǰ�ۺ�ö����</param>
void move_next_polymeric(polymeric_enumerator_t this);
/// <summary>
/// �ۺ�ö������ǰԪ��
/// </summary>
/// <param name="this">��ǰ�ۺ�ö����</param>
/// <returns>��ǰԪ��</returns>
item_t* value_of_polymeric(polymeric_enumerator_t this);
/// <summary>
/// �ͷžۺ�ö����
/// </summary>
/// <param name="this">��ǰ�ۺ�ö����</param>
void destroy_polymeric_enumerator(polymeric_enumerator_t this);

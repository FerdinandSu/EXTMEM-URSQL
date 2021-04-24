#pragma once
#include "ursql-consts.h"

typedef struct relation_t_str
{
	name_t name;
	size_t size;
} relation_t;

/// <summary>
/// ���Դ���һ���µĹ�ϵ
/// </summary>
/// <param name="info">��ϵ��Ϣ</param>
/// <param name="buffer">������</param>
/// <param name="fields">��ϵ�������ֶ�</parm>
/// <returns>�Ƿ񴴽��ɹ�</returns>
bool generate_relation_data(
	relation_t info,
	buffer_t buffer,
	ARRAY(property_info_t) fields
);

/// <summary>
/// ��ȡָ����ϵ�ĵ�ַ
/// </summary>
/// <param name="relation">��ϵ����</param>
/// <returns>��ַ</returns>
address_t address_of(name_t relation);

/// <summary>
/// ��һ����ϵ��ÿһ�����������
/// </summary>
/// <param name="rel">��ϵ��Ϣ</param>
/// <param name="key">�������õļ�</param>
/// <param name="buf"></param>
void sort_each_block(name_t rel, name_t key, buffer_t buf);

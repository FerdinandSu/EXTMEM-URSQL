#pragma once
#include "ursql-consts.h"

/// <summary>
/// ������̿�д��˵��
/// </summary>
/// <param name="left">��һ��</param>
/// <param name="right">���һ��</param>
void comment_wrote_into_blocks(address_t left, address_t right);

/// <summary>
/// �����д����
/// </summary>
/// <param name="buffer">������</param>
void comment_io_times(buffer_t buffer);
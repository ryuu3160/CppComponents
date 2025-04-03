/*+===================================================================
	File: HashGenerator.hpp
	Summary: �n�b�V���l�𐶐�����N���X
	Author: ryuu3160
	Date: 2024/12/03 ����쐬

	(C) 2024 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <sstream>
#include <iomanip>
#include <string>
// ==============================
//	�萔��`
// ==============================

/// <summary>
/// HashGenerator�N���X
/// </summary>
class HashGenerator
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	HashGenerator();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HashGenerator();

	uint32_t GenerateHash(std::string In_String);

private:
	uint32_t *m_pui32Crc32Table;
};

/*+===================================================================
	File: Component.hpp
	Summary: �R���|�[�l���g�̊��N���X
	Author: ryuu3160
	Date: 2025/5/8 Thu AM 01:15:39 ����쐬

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================


/// <summary>
/// Component�N���X
/// </summary>
class Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Component() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Component();

	virtual void Init();
	virtual void Uninit();

private:

};

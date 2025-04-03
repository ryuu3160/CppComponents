/*+===================================================================
	File: Observer.cpp
	Summary: Observer�N���X
	Author: ryuu3160
	Date: 2025/02/07 13:57 ����쐬
				 /09 06:34 �֐��|�C���^��ǉ�����֐���ǉ�
					 06:34 �o�^����Ă���֐���S�Ď��s����֐���ǉ�
					 06:38 �o�^����Ă���֐����N���A����֐���ǉ�

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "Observer.hpp"

Observer::Observer()
{
	// ���X�g���N���A
	m_Function.clear();
}

Observer::~Observer()
{
}

void Observer::AppendFunction(std::function<void()> In_Function, std::string In_strNotifyName)
{
	// �w��̒ʒm���Ŋ֐���ǉ�
	// std::function�����̂܂ܒǉ�
	m_Function[In_strNotifyName].push_back(In_Function);
}

void Observer::Notify(std::string In_strNotifyName)
{
	// �w��̒ʒm�������݂��Ȃ��ꍇ�͉������Ȃ�
	if (m_Function.find(In_strNotifyName) == m_Function.end()) return;

	// �w��̒ʒm���œo�^����Ă���֐���S�Ď��s
	for (auto &Func : m_Function.at(In_strNotifyName))
	{
		Func(); // �֐������s
	}
}

void Observer::ClearFunction(std::string In_strNotifyName)
{
	// �w��̒ʒm�������݂��Ȃ��ꍇ�͉������Ȃ�
	if (m_Function.find(In_strNotifyName) == m_Function.end()) return;

	// �w��̒ʒm���œo�^����Ă���֐���S�č폜
	m_Function.at(In_strNotifyName).clear();
}

void Observer::AllClearFunction()
{
	for (auto &Func : m_Function)
	{
		// �o�^����Ă���֐���S�č폜
		Func.second.clear();
	}
	// ���X�g���N���A
	m_Function.clear();
}

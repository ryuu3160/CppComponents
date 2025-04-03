/*+===================================================================
	File: Observer.hpp
	Summary: Observer�N���X
	Author: ryuu3160
	Date: 2025/02/07 13:57 ����쐬
				 /09 06:34 �֐��|�C���^��ǉ�����֐���ǉ�
					 06:34 �o�^����Ă���֐���S�Ď��s����֐���ǉ�
					 06:38 �o�^����Ă���֐����N���A����֐���ǉ�

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <functional>
#include <string>
#include <unordered_map>
#include <deque>

/// <summary>
/// <para>Observer�N���X</para>
/// <para>�p�����Ďg�p���鎖��z�肵�Ă���</para>
/// </summary>
class Observer
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Observer();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Observer();

	/// <summary>
	/// �ʒm���ɌĂяo���֐���ǉ�����
	/// </summary>
	/// <param name="[In_Function]">�N���X�����o�ȊO�̊֐�</param>
	/// <param name="[In_strNotifyName]">�ʒm��(�w�肵�Ȃ��ꍇ��default)</param>
	void AppendFunction(std::function<void()> In_Function, std::string In_strNotifyName = "default");

	// XML�ł�:��A���Ŏg���Ȃ����߁A���ꂾ��Doxygen
	/**
	* @brief �ʒm���ɌĂяo���֐���ǉ�����
	* @tparam [_Func] �ǉ�����֐��̌^
	* @tparam [_Instance] �ǉ�����֐��̃C���X�^���X�̌^
	* @param [In_Function] �ǉ�����A�N���X�̃����o�֐��ւ̉E�Ӓl�Q��
	* @param [In_Instance] ��L�N���X�̃C���X�^���X�ւ̉E�Ӓl�Q��
	* @details �g�p�� : 
						�ΏۃN���X�̃C���X�^���X���ÓI�I�u�W�F�N�g(new���g�p���Ă��Ȃ�)�̏ꍇ : AppendFunction(&Class::Function, &Instance);
						�ΏۃN���X�̃C���X�^���X�����I�I�u�W�F�N�g(new�Ŋm�ۂ���Ă���)�̏ꍇ : AppendFunction(&Class::Function, Instance);
	*/
	template<typename _Func, typename _Instance>
	void AppendFunction(_Func &&In_Function, _Instance &&In_Instance, std::string In_strNotifyName = "default")
	{
		// �w��̒ʒm���Ŋ֐���ǉ�
		// std::bind�Ŋ֐��ƃC���X�^���X�𑩔����āAstd::function�ɕϊ����Ēǉ�
		// std::forward�ŉE�Ӓl�Q�Ƃ����̂܂ܓn��(�R�s�[�������)(���S�]��)
		m_Function[In_strNotifyName].push_back(std::bind(std::forward<_Func>(In_Function), std::forward<_Instance>(In_Instance)));
	}

	/// <summary>
	/// �ʒm���s��
	/// </summary>
	/// <param name="[In_strNotifyName]">�ʒm��</param>
	void Notify(std::string In_strNotifyName = "default");

	/// <summary>
	/// �ʒm���ɌĂяo���֐���S�č폜����
	/// </summary>
	/// <param name="[In_strNotifyName]">�ʒm��</param>
	void ClearFunction(std::string In_strNotifyName = "default");

	/// <summary>
	/// �ʒm���A�o�^����Ă���֐��A���ɑS�č폜����
	/// </summary>
	void AllClearFunction();

private:
	std::unordered_map<std::string,std::deque<std::function<void()>>> m_Function;
};

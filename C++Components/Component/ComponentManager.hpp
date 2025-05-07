/*+===================================================================
	File: ComponentManager.hpp
	Summary: �R���|�[�l���g�̊Ǘ��N���X(�ǉ���)
	Author: ryuu3160
	Date: 2025/5/8 Thu AM 01:15:12 ����쐬

	(C) 2025 ryuu3160. All rights reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Component.hpp"
#include <list>

/// <summary>
/// ComponentManager�N���X
/// </summary>
class ComponentManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ComponentManager() = default;

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ComponentManager() = default;

	/// <summary>
	/// �R���|�[�l���g�̒ǉ�
	/// </summary>
	/// <param name="[T]">�ǉ�����R���|�[�l���g�̌^</param>
	template<typename T = Component>
	T *AddComponent()
	{
		T *pComponent = new T();
		m_lsComponents.push_back(pComponent);
		// �A�b�v�L���X�g��Component�ɕϊ���A����������
		static_cast<Component *>(pComponent)->Init();
		return pComponent;
	}

	template<typename T = Component>
	T *GetComponent()
	{
		for (auto &component : m_lsComponents)
		{
			if (typeid(*component) == typeid(T))
			{
				return dynamic_cast<T *>(component); // �_�E���L���X�g�ɂ��^�ϊ�
			}
		}
		return nullptr;
	}

protected:
	std::list<Component *> m_lsComponents; // �R���|�[�l���g�̃��X�g
};

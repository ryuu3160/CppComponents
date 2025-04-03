/*+==========================================================================
* File : Singleton.h
* Author : ryuu3160
* Date : 2024/07/27
* Note : mozc���V���O���g��
* 
* (C) 2024 ryuu3160. All Rights Reserved.
=============================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "SingletonController.hpp"

/// <summary>
/// �V���O���g���N���X
/// </summary>
/// <typeparam name="[T]">�V���O���g���ɂ���N���X</typeparam>
template<typename T>
class Singleton
{
public:
    /// <summary>
    /// �C���X�^���X�̎擾
    /// </summary>
    /// <returns>�C���X�^���X�ւ̎Q��</returns>
    static T &GetInstance()
    {
        // �C���X�^���X�������ꍇ�͍쐬
        if(m_instance == nullptr)
            std::call_once(m_onceFlag, create);

        return *m_instance;
    }

protected:
    // �f�t�H���g�R���X�g���N�^�A�f�X�g���N�^
    Singleton() = default;
    virtual ~Singleton() = default;

    // �R�s�[�E����֎~
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    /// <summary>
    /// �C���X�^���X�̍쐬
    /// </summary>
    static void create()
    {
        m_instance = new T;
        SingletonController::AddController(&Singleton<T>::destroy);
    }
    /// <summary>
    /// ���������C���X�^���X�̔j��
    /// </summary>
    static void destroy()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    static std::once_flag m_onceFlag;   // ��x�������������邽�߂̃t���O
    static T *m_instance;               // �C���X�^���X�ւ̃|�C���^
};

template <typename T> std::once_flag Singleton<T>::m_onceFlag;
template <typename T> T *Singleton<T>::m_instance = nullptr;
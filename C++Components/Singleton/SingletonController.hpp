/*+===================================================================
    File: SingletonController.hpp
    Summary: ����V���O���g��
    Author: ryuu3160
    Date: 2024/08/16   ����쐬

    (C) 2024 ryuu3160. All Rights Reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <mutex>
#include <vector>
#include <algorithm>

class SingletonController final
{
public:
    using ControllerFunc = void(*)();   // �֐��|�C���^

    /// <summary>
    /// �V���O���g���N���X�̉��������ǉ�
    /// </summary>
    /// <param name="[func]">destroy�֐��̃|�C���^</param>
    static void AddController(ControllerFunc func);

    /// <summary>
    /// �S�ẴV���O���g���N���X�̉���������Ăяo��
    /// </summary>
    static void Release();
};
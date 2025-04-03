/*+===================================================================
    File: SingletonController.hpp
    Summary: ����V���O���g��
    Author: AT12C192 01 �ؗY��Y
    Date: 2024/08/16   ����쐬

    (C) 2024 Yuichiro Aoki. All Rights Reserved.
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
    static void addController(ControllerFunc func);

    /// <summary>
    /// �S�ẴV���O���g���N���X�̉���������Ăяo��
    /// </summary>
    static void release();
};
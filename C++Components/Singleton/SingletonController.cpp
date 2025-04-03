/*+===================================================================
	File: SingletonController.cpp
	Summary: ����V���O���g��
	Author: AT12C192 01 �ؗY��Y
	Date: 2024/08/16       ����쐬

	(C) 2024 Yuichiro Aoki. All Rights Reserved.
===================================================================+*/

// ==============================
//	include
// ==============================
#include "SingletonController.hpp"

// ==============================
//	�O���[�o���ϐ��錾
// ==============================
namespace
{
std::mutex g_mutex;			// �r������p�̃~���[�e�b�N�X
int g_nControllerCount = 0;	// �Ǘ����ɂ���V���O���g���N���X�̐�

std::vector<SingletonController::ControllerFunc> g_ControllerList; // �I�u�W�F�N�g�j���֐����i�[����Vector
}

void SingletonController::addController(ControllerFunc func)
{
	std::lock_guard<std::mutex> lock(g_mutex); // �����ɃA�N�Z�X����Ȃ��悤�Ƀ��b�N
	if (g_nControllerCount < g_ControllerList.max_size())
	{
		g_ControllerList.push_back(func);
	}
}

void SingletonController::release()
{
	std::lock_guard<std::mutex> lock(g_mutex); // �����ɃA�N�Z�X����Ȃ��悤�Ƀ��b�N

	for (auto func = g_ControllerList.crbegin(); func != g_ControllerList.crend(); func++)
	{
		(*func)();
	}
	g_ControllerList.clear();
}
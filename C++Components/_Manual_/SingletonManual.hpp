/*+===================================================================
	File: SingletonManual.hpp
	Summary: Singleton�̃}�j���A��
	Author: ryuu3160
	Date: 2025/4/4 ����쐬
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../Singleton/Singleton.hpp"
#include <iostream>

// Singleton�N���X���p�����邱�ƂŁA�Ώۂ̃N���X���V���O���g��������
class YourClass : public Singleton<YourClass>
{
	// �K���t�����h�N���X�ɂ��邱��
	// ��������Ȃ��ƁASingleton�N���X���R���X�g���N�^�A�f�X�g���N�^���ĂԂ��Ƃ��ł��Ȃ�
	friend class Singleton<YourClass>;

public:

	// �l�X�Ȋ֐��`
	void SomeFunction()
	{
		std::cout << "SomeFunction\n" << std::endl;
	}

private:

	// �R���X�g���N�^�ƃf�X�g���N�^�͕K��private�ɂ��邱��
	YourClass()
	{
		std::cout << "YourClass�̃R���X�g���N�^\n" << std::endl;
	}
	~YourClass()
	{
		std::cout << "YourClass�̃f�X�g���N�^\n" << std::endl;
	}
};

class YourClass2 : public Singleton<YourClass2>
{
	friend class Singleton<YourClass2>;
public:
	// �l�X�Ȋ֐��`
	void SomeFunction2()
	{
		std::cout << "SomeFunction2\n" << std::endl;
	}
private:
	// �R���X�g���N�^�ƃf�X�g���N�^�͕K��private�ɂ��邱��
	YourClass2()
	{
		std::cout << "YourClass2�̃R���X�g���N�^\n" << std::endl;
	}
	~YourClass2()
	{
		std::cout << "YourClass2�̃f�X�g���N�^\n" << std::endl;
	}
};

void SingletonTest()
{
	std::cout << "====================\n" << std::endl;
	std::cout << "SingletonTest\n" << std::endl;
	std::cout << "====================\n" << std::endl;
	// YourClass�̃C���X�^���X�𐶐�&�擾
	YourClass &instance = YourClass::GetInstance();

	// YourClass2�̃C���X�^���X�𐶐�&�擾
	YourClass2 &instance2 = YourClass2::GetInstance();

	// YourClass�̊֐����Ăяo��
	instance.SomeFunction();

	// YourClass2�̊֐����Ăяo��
	instance2.SomeFunction2();

	// �v���O�����̏I�����ɁASingletonController::Release()���Ăяo�����Ƃ�
	// ���������S�ẴV���O���g���I�u�W�F�N�g���A�����Ƃ͋t���ŉ������
	SingletonController::Release();
}

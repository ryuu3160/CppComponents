/*+===================================================================
	File: Manual.cpp
	Summary: ���p���@�̃T���v��
	Author: ryuu3160
	Date: 2025/4/4 ����쐬
===================================================================+*/

// ==============================
//	include
// ==============================
#include "SingletonManual.hpp"
#include "RandomModuleManual.hpp"
#include <iostream>

int main()
{
	SingletonTest();

	RandomModuleTest();

	static_cast<void>(getchar());
	return 0;
}

/*+===================================================================
	File: Manual.cpp
	Summary: 利用方法のサンプル
	Author: ryuu3160
	Date: 2025/4/4 初回作成
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

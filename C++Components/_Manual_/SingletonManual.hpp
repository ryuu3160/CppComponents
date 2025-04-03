/*+===================================================================
	File: SingletonManual.hpp
	Summary: Singletonのマニュアル
	Author: ryuu3160
	Date: 2025/4/4 初回作成
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "../Singleton/Singleton.hpp"
#include <iostream>

// Singletonクラスを継承することで、対象のクラスをシングルトン化する
class YourClass : public Singleton<YourClass>
{
	// 必ずフレンドクラスにすること
	// これをしないと、Singletonクラスがコンストラクタ、デストラクタを呼ぶことができない
	friend class Singleton<YourClass>;

public:

	// 様々な関数～
	void SomeFunction()
	{
		std::cout << "SomeFunction\n" << std::endl;
	}

private:

	// コンストラクタとデストラクタは必ずprivateにすること
	YourClass()
	{
		std::cout << "YourClassのコンストラクタ\n" << std::endl;
	}
	~YourClass()
	{
		std::cout << "YourClassのデストラクタ\n" << std::endl;
	}
};

class YourClass2 : public Singleton<YourClass2>
{
	friend class Singleton<YourClass2>;
public:
	// 様々な関数～
	void SomeFunction2()
	{
		std::cout << "SomeFunction2\n" << std::endl;
	}
private:
	// コンストラクタとデストラクタは必ずprivateにすること
	YourClass2()
	{
		std::cout << "YourClass2のコンストラクタ\n" << std::endl;
	}
	~YourClass2()
	{
		std::cout << "YourClass2のデストラクタ\n" << std::endl;
	}
};

void SingletonTest()
{
	std::cout << "====================\n" << std::endl;
	std::cout << "SingletonTest\n" << std::endl;
	std::cout << "====================\n" << std::endl;
	// YourClassのインスタンスを生成&取得
	YourClass &instance = YourClass::GetInstance();

	// YourClass2のインスタンスを生成&取得
	YourClass2 &instance2 = YourClass2::GetInstance();

	// YourClassの関数を呼び出す
	instance.SomeFunction();

	// YourClass2の関数を呼び出す
	instance2.SomeFunction2();

	// プログラムの終了時に、SingletonController::Release()を呼び出すことで
	// 生成した全てのシングルトンオブジェクトを、生成とは逆順で解放する
	SingletonController::Release();
}

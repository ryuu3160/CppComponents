/*+===================================================================
	File: ObserverManual.hpp
	Summary: （このファイルで何をするか記載する）
	Author: AT12X192 01 青木雄一郎
	Date: 2025/6/7 Sat PM 01:07:13 初回作成
	（これ以降下に更新日時と更新内容を書く）
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "Observer/Observer.hpp"
#include <iostream>

class EventCall : public Observer
{
public:
	EventCall() = default;
	~EventCall()  = default;
};

class Event1
{
	public:
	Event1() = default;
	~Event1() = default;
	void Event()
	{
		std::cout << "イベント1が発生しました" << std::endl;
	}
};

class Event2
{
	public:
	Event2() = default;
	~Event2() = default;
	void Event()
	{
		std::cout << "イベント2が発生しました" << std::endl;
	}
};

class Event3
{
	public:
	Event3() = default;
	~Event3() = default;
	void Event()
	{
		std::cout << "イベント3が発生しました" << std::endl;
	}
};

class Event4
{
	public:
	Event4() = default;
	~Event4() = default;
	void Event()
	{
		std::cout << "イベント4が発生しました" << std::endl;
	}
};

void ObserverTest()
{
	EventCall *observer = new EventCall();
	Event1 *event1 = new Event1();
	Event2 *event2 = new Event2();
	Event3 *event3 = new Event3();
	Event4 *event4 = new Event4();

	// イベントの登録
	observer->AppendFunction(&Event1::Event, event1);
	observer->AppendFunction(&Event2::Event, event2);
	observer->AppendFunction(&Event3::Event, event3);
	observer->AppendFunction(&Event4::Event, event4);

	// イベントの発生
	std::cout << "イベントを発生させます" << std::endl << std::endl;
	observer->Notify();
}

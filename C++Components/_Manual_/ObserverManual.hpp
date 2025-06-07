/*+===================================================================
	File: ObserverManual.hpp
	Summary: �i���̃t�@�C���ŉ������邩�L�ڂ���j
	Author: AT12X192 01 �ؗY��Y
	Date: 2025/6/7 Sat PM 01:07:13 ����쐬
	�i����ȍ~���ɍX�V�����ƍX�V���e�������j
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
		std::cout << "�C�x���g1���������܂���" << std::endl;
	}
};

class Event2
{
	public:
	Event2() = default;
	~Event2() = default;
	void Event()
	{
		std::cout << "�C�x���g2���������܂���" << std::endl;
	}
};

class Event3
{
	public:
	Event3() = default;
	~Event3() = default;
	void Event()
	{
		std::cout << "�C�x���g3���������܂���" << std::endl;
	}
};

class Event4
{
	public:
	Event4() = default;
	~Event4() = default;
	void Event()
	{
		std::cout << "�C�x���g4���������܂���" << std::endl;
	}
};

void ObserverTest()
{
	EventCall *observer = new EventCall();
	Event1 *event1 = new Event1();
	Event2 *event2 = new Event2();
	Event3 *event3 = new Event3();
	Event4 *event4 = new Event4();

	// �C�x���g�̓o�^
	observer->AppendFunction(&Event1::Event, event1);
	observer->AppendFunction(&Event2::Event, event2);
	observer->AppendFunction(&Event3::Event, event3);
	observer->AppendFunction(&Event4::Event, event4);

	// �C�x���g�̔���
	std::cout << "�C�x���g�𔭐������܂�" << std::endl << std::endl;
	observer->Notify();
}

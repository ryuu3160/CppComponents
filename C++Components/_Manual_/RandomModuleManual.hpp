/*+===================================================================
	File: RandomManual.hpp
	Summary: RandomModule‚Ìƒ}ƒjƒ…ƒAƒ‹
	Author: ryuu3160
	Date: 2025/05/08 ‰‰ñì¬
===================================================================+*/
#pragma once
#include "../RandomModule/Random.hpp"
#include <iostream>

void RandomModuleTest()
{
	Random *pRandom = new Random();
	pRandom->enableMT();

	std::string str;
	for (int i = 0; i < 30; i++)
	{
		str = pRandom->Choice("A");

		std::cout << str;
	}
	
	delete pRandom;
}
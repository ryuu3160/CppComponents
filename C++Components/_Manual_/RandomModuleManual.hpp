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
	std::vector<std::string> vstr;
	std::vector<std::string> Sample;
	vstr.push_back("Hello");
	vstr.push_back("World");
	vstr.push_back("Random");
	vstr.push_back("Module");
	for (int i = 0; i < 10; i++)
	{
		Sample = pRandom->Sample(vstr, 2);

		for (auto &itr : Sample)
			std::cout << itr << "	";
		std::cout << std::endl;
	}
	
	delete pRandom;
}
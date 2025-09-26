#pragma once
#include <iostream>

class Debug
{
public:
	static void Init();
	static void Log(std::string line);
};
#include "Debug.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <dxgi.h>

void Debug::Log(std::string line)
{
#ifdef _DEBUG
	std::cout << line << std::endl;
#endif
}

void Debug::Init()
{
#ifdef _DEBUG
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
    freopen_s(&fp, "CONIN$", "r", stdin);  
    std::cout << "Debug Console" << std::endl;
#endif
}
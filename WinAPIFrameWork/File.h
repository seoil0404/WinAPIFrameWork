#pragma once
#include <filesystem>

#ifdef _DEBUG
inline const std::filesystem::path BasePath = L"D:\\GitHubs\\WinAPIFrameWork\\WinAPIFrameWork";
#else
inline const std::filesystem::path BasePath = L"i don't know";
#endif


#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG //release build
	return "assets/";
#else
	return "/home/henriqu3/Documents/Programas/C-Cpp/C++/LightYears/LightYears/LightYearsGame/assets/";
#endif
}

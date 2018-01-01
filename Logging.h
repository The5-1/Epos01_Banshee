#pragma once
#include <Windows.h>
#include <iostream>

#ifndef LOG(x)
#define LOG(x) do { \
					HANDLE  hConsole;  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, 8);\
					std::cerr << x << std::endl;\
					SetConsoleTextAttribute(hConsole, 15);\
				  } while (0)
#endif // !LOG(x)


#ifndef ERR(x)
#define ERR(x) do { \
						HANDLE  hConsole;  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, 12);\
						std::cerr << "ERROR:\t"<< x  << "\n\tError in Funcion \"" << __func__ << "()\" Line " <<__LINE__<< "\n\tCode File: " << __FILE__ << std::endl; \
						SetConsoleTextAttribute(hConsole, 15);\
					  } while (0)
#endif // !ERR(x)

#ifndef ERR_GL(x)
#define ERR_GL(x) do { \
						HANDLE  hConsole;  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, 13 + 4*16);\
						std::cerr << "OpenGL:\t"<< x  << "\n\tError in Funcion \"" << __func__ << "()\" Line " <<__LINE__<< "\n\tCode File: " << __FILE__ << std::endl; \
						SetConsoleTextAttribute(hConsole, 15);\
					  } while (0)
#endif // !ERR_GL(x)

namespace The5
{
	void enableConsole()
	{
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		LOG("Windows Console enabled.");
	}

	std::string getFilePathWarnings(const std::string &filepath)
	{
		std::string warning("");
		if (filepath.find(':/') == std::string::npos && filepath.find(':\\') == std::string::npos) warning += "\n FILE:\tThere does not seem to be a drive letter present, is this the FULL path?";
		if (filepath.size() < 20) warning += "\n FILE:\tThe Path seems quite short, did you specify the FULL path?";
		return warning;
	}
}

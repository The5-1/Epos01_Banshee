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
	void enableConsole();

	std::string getFilePathWarnings(const std::string &filepath);
}

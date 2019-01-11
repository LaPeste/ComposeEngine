//
//  Utils.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 17/03/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "stdafx.h"
#include "Utils.hpp"
#include <windows.h>

void Utils::PrintDebugLog(const std::string& methodName, const std::string& message)
{
#ifdef LOG_OUTPUT_CONSOLE

	std::ostringstream outstring;
	outstring << "LOG - " << methodName << " : " << message << "\n";
    std::cout << outstring.str();
#ifdef _MSC_VER
	OutputDebugString(outstring.str().c_str());
#endif //_MSC_VER

#endif
}

void Utils::PrintDebugWarning(const std::string& methodName, const std::string& message)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); //green and red form yellow

	std::ostringstream outstring;
	outstring << "WARNING - " << methodName << " : " << message << "\n";
    std::cout << outstring.str();
#ifdef _MSC_VER
	OutputDebugString(outstring.str().c_str());
#endif //_MSC_VER

	//reset settings
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}

void Utils::PrintDebugError(const std::string& methodName, const std::string& message)
{
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);

	std::ostringstream outstring;
	outstring << "ERROR - " << methodName << " : " << message << "\n";
    std::cerr << outstring.str();
#ifdef _MSC_VER
	OutputDebugString(outstring.str().c_str());
#endif //_MSC_VER

	//reset settings
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}

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
	std::ostringstream outstring;
	outstring << "LOG - " << methodName << " : " << message << "\n";
    std::cout << outstring.str();
#ifdef _MSC_VER
	OutputDebugString(outstring.str().c_str());
#endif //_MSC_VER
}

void Utils::PrintDebugWarning(const std::string& methodName, const std::string& message)
{
	std::ostringstream outstring;
	outstring << "WARNING - " << methodName << " : " << message << "\n";
    std::cout << outstring.str();
#ifdef _MSC_VER
	OutputDebugString(outstring.str().c_str());
#endif //_MSC_VER
}

void Utils::PrintDebugError(const std::string& methodName, const std::string& message)
{
	std::ostringstream outstring;
	outstring << "ERROR - " << methodName << " : " << message << "\n";
    std::cerr << outstring.str();
#ifdef _MSC_VER
	OutputDebugString(outstring.str().c_str());
#endif //_MSC_VER
}

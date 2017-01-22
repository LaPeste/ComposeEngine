//
//  Utils.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 17/03/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Utils.hpp"
#include "stdafx.h"

void Utils::PrintDebugLog(const std::string& methodName, const std::string& message)
{
    std::cout << "LOG - " << methodName << " : " << message << "\n";
}

void Utils::PrintDebugWarning(const std::string& methodName, const std::string& message)
{
    std::cout << "WARNING - " << methodName << " : " << message << "\n";
}

void Utils::PrintDebugError(const std::string& methodName, const std::string& message)
{
    std::cout << "ERROR - " << methodName << " : " << message << "\n";
}

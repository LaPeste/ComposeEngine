//
//  Utils.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 17/03/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Utils.h"
#include "stdafx.h"

void Utils::PrintDebug(const std::string& methodName, const std::string& message)
{
    std::cout << methodName << " : " << message << "\n";
}
//
//  Header.h
//  Game Engine 2D
//
//  Created by Andrea Catalini on 17/03/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _UTILS_H_
#define _UTILS_H_

#include "stdafx.h"

class Utils
{
public:
    static void PrintDebugLog(const std::string& methodName, const std::string& message);
    static void PrintDebugWarning(const std::string& methodName, const std::string& message);
    static void PrintDebugError(const std::string& methodName, const std::string& message);
private:
};


#endif /* _UTILS_H_ */

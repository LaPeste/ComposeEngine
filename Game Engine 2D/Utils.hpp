//
//  Header.h
//  Game Engine 2D
//
//  Created by Andrea Catalini on 17/03/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "stdafx.h"

#define DEBUG_LOG(message) Utils::PrintDebugLog(_FUNCTION_NAME_, message)
#define DEBUG_WARNING(message) Utils::PrintDebugWarning(_FUNCTION_NAME_, message)
#define DEBUG_ERROR(message) Utils::PrintDebugError(_FUNCTION_NAME_, message)

class Utils
{
public:
    static void PrintDebugLog(const std::string& methodName, const std::string& message);
    static void PrintDebugWarning(const std::string& methodName, const std::string& message);
    static void PrintDebugError(const std::string& methodName, const std::string& message);

    
private:
};


#endif /* _UTILS_H_ */

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

class Utils
{
public:
    static void PrintDebugLog(const std::string& methodName, const std::string& message);
    static void PrintDebugWarning(const std::string& methodName, const std::string& message);
    static void PrintDebugError(const std::string& methodName, const std::string& message);
    static std::vector<std::string> ComponentsString; //holds all the components in a string fashion, so that they can be used any time a standard operation (like delete call on all components) on all components needs to be performed
    
private:
};


#endif /* _UTILS_H_ */

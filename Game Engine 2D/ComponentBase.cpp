//
//  ComponentBase.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 25/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "ComponentBase.hpp"

unsigned long int ComponentBase::ComponentCounter(0);

ComponentBase::ComponentBase()
{

}

ComponentBase::~ComponentBase()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
	Utils::PrintDebugLog(methodName, "dctr called");
#endif
}

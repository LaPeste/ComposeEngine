//
//  Component.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Component.hpp"

template<typename T>
Component<T>::Component(World& world, const unsigned long int entityIndex) : world(world), entityIndex(entityIndex)
{
    if(Id == 0)
    {
        Id = 1 << ComponentCounter++;
    }
}

template<typename T>
Component<T>::~Component()
{ 
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
	Utils::PrintDebugLog(methodName, "dctr called");
#endif
}

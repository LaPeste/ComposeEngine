//
//  Component.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Component.hpp"
#include <sstream>

template<typename T>
Component<T>::Component()
{
    if(Id == 0)
    {
        Id = 1 << ComponentCounter++;
    }
}

template<typename T>
bool Component<T>::CopyDataToMapObject(World& world, const unsigned long int entityIndex)
{
	std::string methodName = _FUNCION_NAME_;
	Utils::PrintDebugError(methodName, "You are trying to copy data of this component to MapObject but you haven't defined how (overload this method for this component).");
	return false;
}

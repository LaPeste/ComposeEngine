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

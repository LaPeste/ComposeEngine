//
//  GameObjectComponent.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 10/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _GAMEOBJECT_COMPONENT_HPP_
#define _GAMEOBJECT_COMPONENT_HPP_

#include "stdafx.h"

//interface for GameObject Components

class GameObjectComponent
{
    
public:
    virtual void OnInput() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    
private:
    
};

#endif /* _GAMEOBJECT_COMPONENT_HPP_ */

/* THEORY
The C++ interfaces are implemented using abstract classes.
A class is made abstract by declaring at least one of its functions as pure virtual function.
A pure virtual function is specified by placing "= 0" in its declaration as follows

*/
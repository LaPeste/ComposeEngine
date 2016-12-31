//
//  ComponentBase.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 25/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COMPONENT_BASE_HPP_
#define _COMPONENT_BASE_HPP_

#include "stdafx.h"

//Class needed to give a common base to templated components when they need to be fit in the same world component matrix

class ComponentBase
{
public:
    ComponentBase();
    
//    virtual ComponentBase* GetComponent() = 0; //pure virtual class
    
protected:
    static unsigned long int ComponentCounter; //used for assigning a unique id to a component
    
};


#endif /* _COMPONENT_BASE_HPP_ */

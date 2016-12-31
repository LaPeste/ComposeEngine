//
//  Component.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COMPONET_HPP_
#define _COMPONET_HPP_

#include "stdafx.h"
#include "ComponentBase.hpp"
#include "World.hpp"

template<typename T>
class Component : public ComponentBase
{
    
public:
    Component();
    
    static unsigned long int Id;
};

template<typename T>
unsigned long int Component<T>::Id(0);

#include "Component.tpp"

#endif /* _COMPONET_HPP_ */

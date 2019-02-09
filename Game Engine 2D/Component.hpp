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
#include "World.hpp"

template<typename T>
class Component : public ComponentBase
{
    
public:
    Component(World& world, const unsigned long int entityIndex);
	~Component() override;
    
    static unsigned long int Id;

protected:
	World& world;
	const unsigned long int entityIndex;
};

#include "Component.tpp"

#endif /* _COMPONET_HPP_ */

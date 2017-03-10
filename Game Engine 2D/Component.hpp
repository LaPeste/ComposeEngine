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
    Component();
    
    static unsigned long int Id;

	// Needed to be defined when modified data in code needs to be reflected on MapObject entities
	// Returns true if success, false otherwise.
	//TODO if possible world should be const but I am having problems when trying to access a component from a const World&
	virtual bool CopyDataToMapObject(World& world, const unsigned long int entityIndex);
};

template<typename T>
unsigned long int Component<T>::Id(0);

#include "Component.tpp"

#endif /* _COMPONET_HPP_ */

//
//  Collision.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "CollisionEvent.hpp"

CollisionEvent::CollisionEvent(unsigned long indexEntityA, unsigned long indexEntityB) :
	indexEntityA(indexEntityA), indexEntityB(indexEntityB)
{}

const unsigned long int CollisionEvent::GetEntityA() const
{
	return indexEntityA;
}

const unsigned long int CollisionEvent::GetEntityB() const
{
	return indexEntityB;
}

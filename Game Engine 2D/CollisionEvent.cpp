//
//  Collision.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "CollisionEvent.hpp"

CollisionEvent::CollisionEvent(unsigned long indexEntityA, unsigned long indexEntityB)
{
    indexCollidingEntities.x = indexEntityA;
    indexCollidingEntities.y = indexEntityB;
}

const sf::Vector2<unsigned long>& CollisionEvent::GetCollidingEntities() const
{
    return indexCollidingEntities;
}
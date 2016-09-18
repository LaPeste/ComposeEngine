//
//  Collision.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COLLISION_HPP_
#define _COLLISION_HPP_

#include "stdafx.h"

class CollisionEvent
{
public:
    CollisionEvent(unsigned long indexEntityA, unsigned long indexEntityB);
    const sf::Vector2<unsigned long>& GetCollidingEntities() const;
    
private:
    sf::Vector2<unsigned long> indexCollidingEntities;
    
};

#endif /* _COLLISION_HPP_ */

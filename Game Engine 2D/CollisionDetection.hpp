//
//  CollisionDetection.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COLLISION_DETECTION_HPP_
#define _COLLISION_DETECTION_HPP_

#include "stdafx.h"
#include "World.hpp"

#define COLLISION_MASK Components::APPEARANCE | Components::POSITION | Components::FLAG

class CollisionDetection
{
public:
    static bool Collides(const World& world, const unsigned long entityIndex);
private:
    
};

#endif /* _COLLISION_DETECTION_HPP_ */

//
//  CollisionDetection.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COLLISION_DETECTION_UTILS_HPP_
#define _COLLISION_DETECTION_UTILS_HPP_

#include "stdafx.h"
#include "World.hpp"

class CollisionDetectionUtils
{
public:
    static bool Collides(const World& world, const unsigned long entityIndex);
private:
//    static const std::vector<const sf::Vector2f&>* const CalculateCollisionPoint(const World& world, const unsigned long entityIndex);
};

#endif /* _COLLISION_DETECTION_UTILS_HPP_ */

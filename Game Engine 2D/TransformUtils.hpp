//
//  Position.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _TRANSFORM_UTILS_HPP_
#define _TRANSFORM_UTILS_HPP_

#include "stdafx.h"
#include "World.hpp"

class TransformUtils
{
public:
    static const sf::Vector2f& GetPosition(const World& world, unsigned const long entityIndex);
    static void SetPosition(const World& world, unsigned const long entityIndex, sf::Vector2f position);
};

#endif /* _TRANSFORM_UTILS_HPP_ */

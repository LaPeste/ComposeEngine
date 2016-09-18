//
//  Position.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _POSITION_HPP_
#define _POSITION_HPP_

#include "stdafx.h"
#include "World.hpp"

class World; // forward declaration. Position needs world to be defined and world holds a list of Positions

class Position
{
public:
    Position();
    Position(const World& world, unsigned const long entityIndex, float x, float y, bool canJump);
    ~Position();

    const sf::Vector2f& GetPosition(const World& world, unsigned const long entityIndex) const;
    void SetPosition(const World& world, unsigned const long entityIndex, sf::Vector2f position);
    bool CanJump; //used to check conditions like: touching the ground etc etc
};

#endif /* _POSITION_HPP_ */

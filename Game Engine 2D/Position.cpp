//
//  Position.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Position.hpp"

Position::Position() : x(500), y(500), CanJump(false)
{
    
}

Position::~Position()
{
    
}

const sf::Vector2f Position::GetPosition() const
{
    return sf::Vector2f(x, y);
}

void Position::SetPosition(sf::Vector2f position)
{
    x = position.x;
    y = position.y;
}
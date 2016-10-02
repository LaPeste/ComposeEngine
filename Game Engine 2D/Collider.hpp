//
//  Collider.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 02/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COLLIDER_HPP_
#define _COLLIDER_HPP_

#include "stdafx.h"
#include "Appearance.hpp"

class Collider
{
public:
    Collider(const sf::Vector2f& offset);
    
    std::vector<sf::Vector2f> GetCollisionPoints(const Appearance& appearance) const; //returns a set of points big as the sprite bounds plus the offset
    std::vector<sf::Vector2f> GetCollisionPoints() const; //returns a set of points as big as the offset

private:
    sf::Vector2f offset;
};

#endif /* _COLLIDER_HPP_ */

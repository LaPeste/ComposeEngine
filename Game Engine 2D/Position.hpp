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

class Position
{
public:
    Position();
    ~Position();

    const sf::Vector2f GetPosition() const;
    void SetPosition(sf::Vector2f position);
    bool CanJump; //used to check conditions like: touching the ground etc etc
    
private:
    float x, y;

};

#endif /* _POSITION_HPP_ */

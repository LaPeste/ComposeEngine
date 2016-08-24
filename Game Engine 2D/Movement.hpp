//
//  Movement.h
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _MOVEMENT_HPP_
#define _MOVEMENT_HPP_

#include "stdafx.h"
#include "World.hpp"
#include "Components.hpp"
#include "SystemBase.hpp"

#define MOVEMENT_MASK Components::POSITION | Components::VELOCITY | Components::ACCELERATION | Components::CONTROLLER | Components::FLAG | Components::APPEARANCE

class Movement : public SystemBase
{
public:
    Movement();
    ~Movement();
    
    void OnUpdate() override;
    
private:
    void MoveEntity(const World& world, const unsigned long entityIndex);
    void StopMove(const World& world, const unsigned long entityIndex);
    bool Jump(const World& world, const unsigned long entityIndex);
    void MoveTo(const World& world, const unsigned long entityIndex, float x, float y);
    bool PosValid(const World& world, const unsigned long entityIndex, float x, float y);
};

#endif /* _MOVEMENT_HPP_ */

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
#include "Components.hpp"
#include "System.hpp"

#define MOVEMENT_MASK Components::CONTROLLER | Components::VELOCITY | Components::ACCELERATION | Components::FLAG | Components::APPEARANCE

template<typename First, typename ...Rest>
class Movement : public System<First,Rest...>
{
public:
    Movement(World& world);
    ~Movement();
    
    void OnUpdate() override;
    bool Jump(const World& world, const unsigned long entityIndex);
    
private:
    void MoveEntity(const World& world, const unsigned long entityIndex);
    void StopMove(const World& world, const unsigned long entityIndex);
    void MoveTo(const World& world, const unsigned long entityIndex, float x, float y);
    bool PosValid(const World& world, const unsigned long entityIndex, float x, float y);
};

#include "Movement.tpp"

#endif /* _MOVEMENT_HPP_ */

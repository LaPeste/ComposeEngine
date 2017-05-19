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
#include "System.hpp"
#include "Controller.hpp"
#include "Velocity.hpp"
#include "Collider.hpp"
#include "Acceleration.hpp"
#include "EntityFlag.hpp"
#include "Transform.hpp"

class Movement : public System<Controller, Velocity, Acceleration, EntityFlag, Transform, Collider>
{
public:
    Movement(World& world);
    ~Movement();
        
private:
    void MoveEntity(World& world, const unsigned long entityIndex);
    void StopMove(World& world, const unsigned long entityIndex);
    void MoveTo(World& world, const unsigned long entityIndex, float x, float y);
    bool PosValid(World& world, const unsigned long entityIndex, float x, float y);

	void Update(World& world, const unsigned long entityIndex) override;

};

#endif /* _MOVEMENT_HPP_ */

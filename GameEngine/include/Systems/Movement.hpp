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
#include "Systems/System.hpp"
#include "Components/Controller.hpp"
#include "Components/Velocity.hpp"
#include "Components/Collider.hpp"
#include "Components/Acceleration.hpp"
#include "Components/EntityFlag.hpp"
#include "Components/Transform.hpp"

class Movement : public System<Controller, Velocity, Acceleration, EntityFlag, Transform, Collider>
{
public:
    Movement(World& world);
    ~Movement() override;
        
private:
    void StopMove(World& world, const unsigned long entityIndex);
    void MoveTo(World& world, const unsigned long entityIndex, float x, float y);
    bool PosValid(World& world, const unsigned long entityIndex, float x, float y);

	void Update(World& world, const unsigned long entityIndex) override;

	bool Jump(World& world, const unsigned long entityIndex);

};

#endif /* _MOVEMENT_HPP_ */

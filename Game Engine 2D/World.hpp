//
//  World.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "stdafx.h"
#include "Acceleration.hpp"
#include "Appearance.hpp"
#include "Position.hpp"
#include "Velocity.hpp"
#include "Controller.hpp"
#include "EntityFlag.hpp"
#include "Components.hpp"
//#include "Collision.hpp"

//TODO I'm not sure if this class should be static... consider that. The question is: would you have more than 1 world per time? If so, then you don't want it static, if no
//then you do want it static

class Position;

class World
{
public:
    World();
    ~World();
    
//private: TODO maybe make them private and use properties?
    std::vector<Components> EntitiesMasks; //defines components held by each entity
    
    //components arrays
    std::vector<Acceleration*> Acceleration;
    std::vector<Appearance*> Appearance;
    std::vector<Controller*> Controller;
    std::vector<Position*> Position;
    std::vector<Velocity*> Velocity;
    std::vector<EntityFlag*> EntityFlag;
//    std::vector<Collision*> Collision;
};

#endif /* _WORLD_HPP_ */

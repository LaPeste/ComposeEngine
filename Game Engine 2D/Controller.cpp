//
//  Controller.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Controller.hpp"

Controller::Controller(World& world, const unsigned long int entityIndex) : MoveRight(false), MoveLeft(false), Crouch(false),
Component(world, entityIndex)
{
    
}

Controller::~Controller() {}

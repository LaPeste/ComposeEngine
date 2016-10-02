//
//  World.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "World.hpp"
//#include "Acceleration.hpp"
//#include "Appearance.hpp"
//#include "Controller.hpp"
//#include "Position.hpp"
//#include "Velocity.hpp"


World::World() /*:
    EntitiesMasks(),
    Acceleration(),
    Appearance(),
    Controller(),
    Position(),
    Velocity(),
    EntityFlag() */
{
    
}

World::~World()
{
    for(std::vector<Acceleration::Acceleration*>::iterator elem_it = Acceleration.begin(); elem_it != Acceleration.end(); ++elem_it)
    {
        delete *elem_it;
    }
    for(std::vector<Appearance::Appearance*>::iterator elem_it = Appearance.begin(); elem_it != Appearance.end(); ++elem_it)
    {
        delete *elem_it;
    }
    for(std::vector<Controller::Controller*>::iterator elem_it = Controller.begin(); elem_it != Controller.end(); ++elem_it)
    {
        delete *elem_it;
    }
//    for(std::vector<Position::Position*>::iterator elem_it = Position.begin(); elem_it != Position.end(); ++elem_it)
//    {
//        delete *elem_it;
//    }
    for(std::vector<Velocity::Velocity*>::iterator elem_it = Velocity.begin(); elem_it != Velocity.end(); ++elem_it)
    {
        delete *elem_it;
    }
    for(std::vector<Collider::Collider*>::iterator elem_it = Collider.begin(); elem_it != Collider.end(); ++elem_it)
    {
        delete *elem_it;
    }
    for(std::vector<EntityFlag::EntityFlag*>::iterator elem_it = EntityFlag.begin(); elem_it != EntityFlag.end(); ++elem_it)
    {
        delete *elem_it;
    }
    for(std::vector<Animation::Animation*>::iterator elem_it = Animation.begin(); elem_it != Animation.end(); ++elem_it)
    {
        delete *elem_it;
    }
}
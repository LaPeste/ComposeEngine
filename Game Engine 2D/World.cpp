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
    EntitiesComponentsMasks(),
    Acceleration(),
    Appearance(),
    Controller(),
    Position(),
    Velocity(),
    EntityFlag() */
{
//    EntitiesComponentsMasks;
//    EntitiesComponentsMatrix;
}

World::~World()
{
    for(const auto& system : Systems)
    {
        delete system.second;
    }
    
    for(std::map<unsigned long int, ComponentBase*>& entity : EntitiesComponentsMatrix)
    {
        for(const auto& component : entity)
        {
            delete component.second;
        }
    }
}

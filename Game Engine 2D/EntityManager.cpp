//
//  EntityManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "EntityManager.hpp"
#include "Components.hpp"

unsigned long EntityManager::playerId(-1);

const unsigned long EntityManager::CreateEntity(World& world)
{
    for(int i = 0; i < world.EntitiesMasks.size(); ++i)
    {
        if(world.EntitiesMasks[i] == Components::NONE) //then a corrispondent position in the components array already exist
        {
            return i;
        }
    }
    
    //TODO maybe do a factory that satisfies all the initialization and the rest of usage of all the components.
    //now it is shuttered all over and it's getting out of controll to manage every little thing, each time that a new component is out
    
//    Components* compNone = new Components;
//    compNone
    
    world.EntitiesMasks.push_back(Components::NONE);
    world.Acceleration.push_back(new Acceleration(0,0));
    world.Appearance.push_back(new Appearance);
    world.Controller.push_back(new Controller);
    world.Position.push_back(new Position);
    world.Velocity.push_back(new Velocity);
    world.EntityFlag.push_back(new EntityFlag);
    
    return world.EntitiesMasks.size() - 1; //return size because you want to return an index that points to a newer
}

void EntityManager::DestroyEntity(World& world, const unsigned long index)
{
//    *world.EntitiesMasks[index] = Components::NONE;
    world.EntitiesMasks[index] = Components::NONE;
}

const unsigned long EntityManager::GetPlayerId()
{
    return playerId;
}

void EntityManager::SetPlayerId(const unsigned long index)
{
    playerId = index;
}


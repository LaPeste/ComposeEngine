//
//  EntityManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "EntityManager.hpp"
#include "Components.hpp"
#include <tmx/MapLoader.h>
#include "Engine.hpp"

unsigned long EntityManager::playerId(NAN);
std::vector<CollisionEvent> EntityManager::collisionEvents;

void EntityManager::Init(World& world)
{
    //populates the list of objects with objects coming from the map (tmx file)
    std::vector<tmx::MapLayer>& layers = Engine::GetInstance().GetMapLoader().GetLayers();
    for(std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
    {
        if(layer->name == Constants::COLLISION_LAYER)
        {
            for(std::vector<tmx::MapObject>::iterator object = layer->objects.begin(); object != layer->objects.end(); ++object)
            {
                //TODO most likely here I need to do more checks, because I may not want to add all the objects in this layer
                const unsigned long indexNewEntity = CreateEntity(world);
                world.EntitiesMasks[indexNewEntity] = /*Components::APPEARANCE |*/ Components::COLLIDER | Components::FLAG;
                world.Collider[indexNewEntity] = new Collider(sf::Vector2f(0,0));
//                world.Appearance[indexNewEntity] = new Appearance(nullptr); //TODO strange that I can't get the sprite from the mapObject
                world.EntityFlag[indexNewEntity] = new EntityFlag(GameObjectFlag::MAP_OBJECT);
                object->SetProperty(Constants::ENTITY_INDEX_PROPERTY, std::to_string(indexNewEntity));
            }

        }
    }
}

const unsigned long EntityManager::CreateEntity(World& world)
{
    for(int i = 0; i < world.EntitiesMasks.size(); ++i)
    {
        if(world.EntitiesMasks[i] == Components::NONE) //then a corrispondent position in the components array already exist
        {
            FreeWorldFields(world, i);
            return i;
        }
    }
    
    //TODO maybe do a factory that satisfies all the initialization and the rest of usage of all the components.
    //now it is shuttered all over and it's getting out of controll to manage every little thing, each time that a new component is out
    
//    Components* compNone = new Components;
//    compNone
    
    world.EntitiesMasks.push_back(Components::NONE);
    world.Acceleration.push_back(new Acceleration(0,0));
    world.Appearance.push_back(new Appearance(nullptr));
    world.Controller.push_back(new Controller);
    world.Velocity.push_back(new Velocity);
    world.EntityFlag.push_back(new EntityFlag);
    world.Collider.push_back(new Collider(sf::Vector2f(0,0)));
    world.Animation.push_back(new Animation);
    
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

void EntityManager::FreeWorldFields(World& world, const int index)
{
    world.EntitiesMasks[index] = Components::NONE;
//    for(int i = 0; i <= Utils::ComponentsString.size(); ++i) //TODO try to call free with the invoke
//    {
//        std::string component = Utils::ComponentsString[i];
//        std::invoke(delete, "world." + Utils::ComponentsString[i]);
//    }
    delete world.Acceleration[index];
    delete world.Appearance[index];
    delete world.Controller[index];
    delete world.EntityFlag[index];
    delete world.Velocity[index];
    delete world.Collider[index];
    delete world.Animation[index];
}

const std::vector<CollisionEvent>& EntityManager::GetCollisionEvents()
{
    return collisionEvents;
}

void EntityManager::AddCollisionEvent(const CollisionEvent& event)
{
    collisionEvents.push_back(event);
}

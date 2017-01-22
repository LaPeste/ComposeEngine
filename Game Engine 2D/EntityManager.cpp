//
//  EntityManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "EntityManager.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"
#include "Collider.hpp"
#include "EntityFlag.hpp"

unsigned long int EntityManager::playerId(99999); //defaulted to a very big number
std::vector<CollisionEvent> EntityManager::collisionEvents;

void EntityManager::Init(World& world)
{
    //populates the list of objects with objects coming from the map (tmx file)
    std::vector<tmx::MapLayer>& layers = Engine::GetInstance().GetMapLoader().getLayers();
    for(std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
    {
        if(layer->name == Constants::COLLISION_LAYER)
        {
            for(std::vector<tmx::MapObject>::iterator object = layer->objects.begin(); object != layer->objects.end(); ++object)
            {
                //TODO most likely here I need to do more checks, because I may not want to add all the objects in this layer
                const unsigned long indexNewEntity = CreateEntity(world);
                AddComponent(world, indexNewEntity, new Collider(sf::Vector2f(0,0)));
//                world.Appearance[indexNewEntity] = new Appearance(nullptr); //TODO strange that I can't get the sprite from the mapObject
                AddComponent(world, indexNewEntity, new EntityFlag(GameObjectFlag::MAP_OBJECT));
                object->setProperty(Constants::ENTITY_INDEX_PROPERTY, std::to_string(indexNewEntity));
            }

        }
    }
}

const unsigned long EntityManager::CreateEntity(World& world)
{
    for(int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
    {
        if(world.EntitiesComponentsMasks[i] == UtilConstants::NO_COMPONENTS) //then a corrispondent position in the components array already exist
        {
            FreeWorldFields(world, i);
            return i;
        }
    }
    
    world.EntitiesComponentsMasks.push_back(UtilConstants::NO_COMPONENTS);
    world.EntitiesComponentsMatrix.push_back(std::map<unsigned long int, ComponentBase*>());
    
    return world.EntitiesComponentsMasks.size() - 1; //return size because you want to return an index that points to a newest entity
}

void EntityManager::DestroyEntity(World& world, const unsigned long index)
{
//    *world.EntitiesComponentsMasks[index] = Components::NONE;
    world.EntitiesComponentsMasks[index] = UtilConstants::NO_COMPONENTS;
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
    world.EntitiesComponentsMasks[index] = UtilConstants::NO_COMPONENTS;
//    for(int i = 0; i <= Utils::ComponentsString.size(); ++i) //TODO try to call free with the invoke
//    {
//        std::string component = Utils::ComponentsString[i];
//        std::invoke(delete, "world." + Utils::ComponentsString[i]);
//    }
//    delete world.Acceleration[index];
//    delete world.Appearance[index];
//    delete world.Controller[index];
//    delete world.EntityFlag[index];
//    delete world.Velocity[index];
//    delete world.Collider[index];
//    delete world.Animation[index];
}

const std::vector<CollisionEvent>& EntityManager::GetCollisionEvents()
{
    return collisionEvents;
}

void EntityManager::AddCollisionEvent(const CollisionEvent& event)
{
    collisionEvents.push_back(event);
}

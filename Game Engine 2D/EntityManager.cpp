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
#include "Acceleration.hpp"
#include "Controller.hpp"
#include "Velocity.hpp"
#include "Transform.hpp"
#include "EntityFlag.hpp"

unsigned long int EntityManager::playerId(99999); //defaulted to a very big number
std::vector<CollisionEvent> EntityManager::collisionEvents;

void EntityManager::Init(World& world)
{
	//test entity for collision test purpose
	const unsigned long entityIndex = EntityManager::CreateEntity(world, GameObjectFlag::GRAVITY);
	EntityManager::AddComponent(world, entityIndex, new Appearance(world, entityIndex, Constants::RESOURCE_PATH + Constants::PLAYER_SPRITE_PATH));
	Appearance* appearance = static_cast<Appearance*>(world.EntitiesComponentsMatrix[entityIndex][Appearance::Id]);
	sf::IntRect spriteRect(498, 12, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
	appearance->GetSprite()->setTextureRect(spriteRect);
	EntityManager::AddComponent(world, entityIndex, new Transform(world, entityIndex));
	Transform* trans = static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]);
	trans->SetPosition(sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X + 30, Constants::PLAYER_PHYSICAL_STARTING_Y + 87 ));
	EntityManager::AddComponent(world, entityIndex, new Collider(world, entityIndex, sf::Vector2f(0, 0), sf::FloatRect(trans->GetPosition().x, trans->GetPosition().y, 20, 20)));
	EntityManager::AddComponent(world, entityIndex, new Acceleration(world, entityIndex, Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y));
	EntityManager::AddComponent(world, entityIndex, new Controller(world, entityIndex));
	EntityManager::AddComponent(world, entityIndex, new Velocity(world, entityIndex));
	
    //populates the list of objects with objects coming from the map (tmx file)
//    std::vector<tmx::MapLayer>& layers = Engine::GetInstance().GetMapLoader().getLayers();
//    for(std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
//    {
//        if(layer->name == Constants::COLLISION_LAYER)
//        {
//            for(std::vector<tmx::MapObject>::iterator object = layer->objects.begin(); object != layer->objects.end(); ++object)
//            {
//                //TODO most likely here I need to do more checks, because I may not want to add all the objects in this layer
//                const unsigned long indexNewEntity = CreateEntity(world, GameObjectFlag::MAP_OBJECT);
//                AddComponent(world, indexNewEntity, new Collider(sf::Vector2f(0,0)));
//				AddComponent(world, indexNewEntity, new Transform());
//				(static_cast<Transform*>(world.EntitiesComponentsMatrix[indexNewEntity][Transform::Id]))->SetPosition(world, indexNewEntity, object->getPosition());
////                world.Appearance[indexNewEntity] = new Appearance(nullptr); //TODO strange that I can't get the sprite from the mapObject
//				AddComponent(world, indexNewEntity, new MapObjectComponent());
//                object->setProperty(Constants::ENTITY_INDEX_PROPERTY, std::to_string(indexNewEntity));
//            }
//
//        }
//    }
}

const unsigned long EntityManager::CreateEntity(World& world, const GameObjectFlag& flags)
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

	unsigned long int indexNewEntity = world.EntitiesComponentsMasks.size() - 1;
	AddComponent(world, indexNewEntity, new EntityFlag(world, indexNewEntity, flags));
    
    return indexNewEntity; //return size because you want to return an index that points to a newest entity
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
}

const std::vector<CollisionEvent>& EntityManager::GetCollisionEvents()
{
    return collisionEvents;
}

void EntityManager::AddCollisionEvent(const CollisionEvent& event)
{
    collisionEvents.push_back(event);
}

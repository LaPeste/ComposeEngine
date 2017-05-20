//
//  EntityManager.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _ENTITY_MANAGER_HPP_
#define _ENTITY_MANAGER_HPP_

#include "stdafx.h"
#include "World.hpp"
#include "Player.hpp"
#include "CollisionEvent.hpp"
#include "Component.hpp"
#include "GameObjectType.hpp"

// Entities represent a game objects as an aggregation of components


class EntityManager
{
public:
    static void Init(World& world);


	template<typename GAME_OBJECT_TYPE>
	static GAME_OBJECT_TYPE* const Instantiate(World& world); //world is a pointer here cause otherwise I'd have had to define the constructor in all subclasses of gameobject. because a reference can never be null at any time while a pointer can.

    static void DestroyGameObject(GameObject* gameObject);

    static const unsigned long GetPlayerId();
    static void SetPlayerId(const unsigned long index);
    
    static const std::vector<CollisionEvent>& GetCollisionEvents();
    static void AddCollisionEvent(const CollisionEvent& event);
    
    template<typename T>
    static void AddComponent(World& world, const unsigned long int entityIndex, Component<T>* componentToAdd);
    
private:
    static unsigned long int playerId;

	//Returns index to entity with no components, if found, otherwise the list will be extended and the latest index returned
	static const unsigned long CreateEntity(World& world, const GameObjectFlag& flags = GameObjectFlag::NONE);

	//Free memory of column matrix
    static void FreeWorldFields(World& world, const int worldIndex);
    static std::vector<CollisionEvent> collisionEvents;

	static void DeleteAllComponentsForEntity(World& world, unsigned long int entityIndex);
	static void DeleteEntityHandle(World& world, unsigned long int entityIndex);
};




/*
 *
 *      TEMPLATED METHODS IMPLEMENTATIONS
 *
 */

template<typename T>
void EntityManager::AddComponent(World& world, const unsigned long int entityIndex, Component<T>* componentToAdd)
{
    world.EntitiesComponentsMasks[entityIndex] |= Component<T>::Id;
    
    std::map<unsigned long int, ComponentBase*>& entityComponentsMap = world.EntitiesComponentsMatrix[entityIndex];
    
#ifdef LOG_OUTPUT_CONSOLE
    std::stringstream ss;
    ss << "ComponentId: " << Component<T>::Id << " entityIndex: " << entityIndex << " component: " << typeid(T).name();
    std::string s = ss.str();
	std::string methodName = _FUNCION_NAME_;
    Utils::PrintDebugLog(methodName, s);
#endif
    
    if(entityComponentsMap.find(Component<T>::Id) == entityComponentsMap.end())    //if key found
    {
        entityComponentsMap.insert(std::make_pair(Component<T>::Id, componentToAdd));
    }
    else
    {
        std::stringstream ss;
        ss << "component " << typeid(T).name() << " already added to entity " << entityIndex << ".";
        std::string s = ss.str();
		std::string methodName = _FUNCION_NAME_;
        Utils::PrintDebugWarning(methodName, s);

    }
}

template<typename GAME_OBJECT_TYPE>
GAME_OBJECT_TYPE* const EntityManager::Instantiate(World& world)
{
	unsigned long int entityIndex = CreateEntity(world, GameObjectFlag::GRAVITY);
	if (typeid(GAME_OBJECT_TYPE) == typeid(Player)) EntityManager::SetPlayerId(entityIndex);
	
	GAME_OBJECT_TYPE* gameObject = new GAME_OBJECT_TYPE;
	gameObject->entityIndex = entityIndex;
	gameObject->world = &world;
	world.EntitiesHandles.insert(std::make_pair(entityIndex, gameObject));
	gameObject->Init();

#ifdef LOG_OUTPUT_CONSOLE
	std::stringstream ss;
	ss << "GameObject " << typeid(GAME_OBJECT_TYPE).name() << " with id " << entityIndex << " has been instantiated!";
	std::string s = ss.str();
	std::string methodName = _FUNCION_NAME_;
	Utils::PrintDebugLog(methodName, s);
#endif

	return gameObject;
}

#endif /* _ENTITY_MANAGER_HPP_ */

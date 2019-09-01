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
#include "GameObjects/GameObjectType.hpp"
#include "Events/AddedComponentEvent.hpp"
#include "Events/EventManager.hpp"
//#include "GameObjects/Player.hpp"
class Player;
// Entities represent a game objects as an aggregation of components

class EntityManager
{
public:
    static void Init(World& world);

    static const unsigned long GetPlayerId();

	template<typename GAME_OBJECT_TYPE>
	static GAME_OBJECT_TYPE* const Instantiate(World& world); //world is a pointer here cause otherwise I'd have had to define the constructor in all subclasses of gameobject. because a reference can never be null at any time while a pointer can.

    static void DestroyGameObject(GameObject* gameObject);

    
    template<typename T>
    static void AddComponent(World& world, const unsigned long int entityIndex, Component<T>* componentToAdd);

	static GameObject& GetGameObject(World& world, unsigned long int entityIndex);

private:
	friend class Player;
    static void SetPlayerId(const unsigned long index);
    static unsigned long int playerId;

	//! Returns index to entity with no components, if found, otherwise the list will be extended and the latest index returned
	static const unsigned long CreateEntity(World& world, const GameObjectFlag& flags = GameObjectFlag::NONE);

	//! Free memory of column matrix
    static void FreeWorldFields(World& world, const int worldIndex);

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
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugLog(methodName, s);
#endif
    
    if(entityComponentsMap.find(Component<T>::Id) == entityComponentsMap.end())    //if not key found
    {
        entityComponentsMap.insert(std::make_pair(Component<T>::Id, componentToAdd));
    }
    else
    {
        std::stringstream ss;
        ss << "component " << typeid(T).name() << " already added to entity " << entityIndex << ".";
        std::string s = ss.str();
		std::string methodName = _FUNCTION_NAME_;
        Utils::PrintDebugWarning(methodName, s);

    }

	auto gameObject = world.EntitiesHandles.find(entityIndex);
	if (gameObject != world.EntitiesHandles.end())
	{
		EventManager::QueueEvent(new AddedComponentEvent(*gameObject->second));
	}
}

template<typename GAME_OBJECT_TYPE>
GAME_OBJECT_TYPE* const EntityManager::Instantiate(World& world)
{
	unsigned long int entityIndex = CreateEntity(world, GameObjectFlag::GRAVITY);
	//if (typeid(GAME_OBJECT_TYPE) == typeid(Player)) EntityManager::SetPlayerId(entityIndex);
	
	GAME_OBJECT_TYPE* gameObject = new GAME_OBJECT_TYPE;
	gameObject->entityIndex = entityIndex;
	gameObject->world = &world;
	auto pair = std::make_pair(entityIndex, gameObject);
	world.EntitiesHandles.insert(pair);
	gameObject->Init();

#ifdef LOG_OUTPUT_CONSOLE
	std::stringstream ss;
	ss << "GameObject " << typeid(GAME_OBJECT_TYPE).name() << " with id " << entityIndex << " has been instantiated!";
	std::string s = ss.str();
	std::string methodName = _FUNCTION_NAME_;
	Utils::PrintDebugLog(methodName, s);
#endif

	return gameObject;
}

#endif /* _ENTITY_MANAGER_HPP_ */

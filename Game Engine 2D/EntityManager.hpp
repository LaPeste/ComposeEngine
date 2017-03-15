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
#include <utility>

// Entities represent a game object as an aggregation of components

class EntityManager
{
public:
    static void Init(World& world);
    static const unsigned long CreateEntity(World& world, const GameObjectFlag& flags = GameObjectFlag::NONE); //returns index to entity with no components, if found, otherwise the list will be extended and the latest index returned
    static void DestroyEntity(World& world, const unsigned long index);
    
    static const unsigned long GetPlayerId();
    static void SetPlayerId(const unsigned long index);
    
    static const std::vector<CollisionEvent>& GetCollisionEvents();
    static void AddCollisionEvent(const CollisionEvent& event);
    
    template<typename T>
    static void AddComponent(World& world, const unsigned long int entityIndex, Component<T>* componentToAdd);
    
private:
    static unsigned long int playerId;
    static void FreeWorldFields(World& world, const int worldIndex); //free memory of column matrix
    static std::vector<CollisionEvent> collisionEvents;
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

#endif /* _ENTITY_MANAGER_HPP_ */

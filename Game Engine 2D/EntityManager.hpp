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

// Entities represent a game object as an aggregation of components

class EntityManager
{
public:
    static void Init(World& world);
    static const unsigned long CreateEntity(World& world); //returns index to entity with no components, if found, otherwise the list will be extended and the latest index returned
    static void DestroyEntity(World& world, const unsigned long index);
    
    static const unsigned long GetPlayerId();
    static void SetPlayerId(const unsigned long index);
    
    static const std::vector<CollisionEvent>& GetCollisionEvents();
    static void AddCollisionEvent(const CollisionEvent& event);
    
private:
    static unsigned long playerId;
    static void FreeWorldFields(World& world, const int worldIndex); //free memory of column matrix
    static std::vector<CollisionEvent> collisionEvents;
};

#endif /* _ENTITY_MANAGER_HPP_ */

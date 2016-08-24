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

// Entities represent a game object as an aggregation of components

class EntityManager
{
public:
    static const unsigned long CreateEntity(World& world); //returns index to entity with no components, if found, otherwise the list will be extended and the latest index returned
    static void DestroyEntity(World& world, const unsigned long index);
    
    static const unsigned long GetPlayerId();
    static void SetPlayerId(const unsigned long index);
    
private:
    static unsigned long playerId;
};

#endif /* _ENTITY_MANAGER_HPP_ */

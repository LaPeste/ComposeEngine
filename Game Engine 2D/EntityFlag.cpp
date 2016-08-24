//
//  EntityFlag.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "EntityFlag.hpp"

EntityFlag::EntityFlag()
{
    
}

const GameObjectFlag& EntityFlag::GetEntityFlag() const
{
    return flag;
}

void EntityFlag::SetNewEntityFlag(const GameObjectFlag &flag)
{
    EntityFlag::flag = flag;
}

void EntityFlag::AddFlagToEntity(const GameObjectFlag &flag)
{
    EntityFlag::flag = EntityFlag::flag | flag;
}
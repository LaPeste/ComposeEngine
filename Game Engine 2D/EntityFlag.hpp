//
//  EntityFlag.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _ENTITY_FLAGH_HPP_
#define _ENTITY_FLAGH_HPP_

#include "stdafx.h"
#include "GameObjectType.hpp"

class EntityFlag
{
public:
    EntityFlag();
    EntityFlag(GameObjectFlag flags);
    
    const GameObjectFlag& GetEntityFlag() const;
    void SetNewEntityFlag(const GameObjectFlag& flag);
    void AddFlagToEntity(const GameObjectFlag& flag);
    
private:
    GameObjectFlag flag;
};

#endif /* _ENTITY_FLAGH_HPP_ */

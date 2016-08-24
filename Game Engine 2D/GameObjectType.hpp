//
//  GameObjectType.h
//  GameEngine2D
//
//  Created by Andrea Catalini on 13/06/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _GAMEOBJECT_TYPE_H_
#define _GAMEOBJECT_TYPE_H_

#include "stdafx.h"
#include "GameObjectType.hpp"



enum class GameObjectType
{
    UserPlayer, Enemy, MapCollisionObject
};

enum class GameObjectFlag
{
    NONE = 0,
    GHOST = 0x00000001,
    GRAVITY = 0x00000002,
    MAPONLY = 0x00000004
};

inline GameObjectFlag operator| (GameObjectFlag a, GameObjectFlag b)
{
    return static_cast<GameObjectFlag>(static_cast<int>(a) | static_cast<int>(b));
}

inline GameObjectFlag operator& (GameObjectFlag a, GameObjectFlag b)
{
    return static_cast<GameObjectFlag>(static_cast<int>(a) & static_cast<int>(b));
}

#endif /* _GAMEOBJECT_TYPE_H_ */

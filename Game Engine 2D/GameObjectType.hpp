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

enum class GameObjectType
{
    UserPlayer, Enemy, MapCollisionObject
};

enum class GameObjectFlags
{
    NONE = 0,
    GHOST = 0x00000001,
    GRAVITY = 0x00000002,
    MAPONLY = 0x00000004
};

#endif /* _GAMEOBJECT_TYPE_H_ */

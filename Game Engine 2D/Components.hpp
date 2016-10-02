//
//  Component.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include "stdafx.h"

// Components represent the data that a game object can have

enum class Components
{
    NONE = 0,
    ACCELERATION = 1 << 0,
    CONTROLLER = 1 << 1,
    APPEARANCE = 1 << 2,
    POSITION = 1 << 3,
    VELOCITY = 1 << 4,
    FLAG = 1 << 5,
    ANIMATION = 1 << 6,
    COLLIDER = 1 << 7
};

inline Components operator| (Components a, Components b)
{
    return static_cast<Components>(static_cast<int>(a) | static_cast<int>(b));
};

inline Components operator& (Components a, Components b)
{
    return static_cast<Components>(static_cast<int>(a) & static_cast<int>(b));
};

//inline bool operator== (int a, Components b) //I can't make this work when it comes to chain more components, like the case right below
//{
//    return a == static_cast<int>(b);
//};

//class Component
//{
//public:
//    static enum Components;
//};

#endif /* _COMPONENT_HPP_ */

//
//  World.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "stdafx.h"
#include <unordered_set>
#include "ComponentBase.hpp"
#include "SystemBase.hpp"


class World
{
public:
    World();
    ~World();
    
//private: TODO maybe make them private and use properties?
    std::vector<unsigned long int> EntitiesComponentsMasks; //defines components held by each entity
    
    std::vector<std::map<unsigned long int, ComponentBase*>> EntitiesComponentsMatrix;
    
    std::map<unsigned long int, SystemBase*> Systems;
};



#endif /* _WORLD_HPP_ */

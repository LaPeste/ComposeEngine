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

//#include "Acceleration.hpp"
//#include "Appearance.hpp"
//#include "Velocity.hpp"
//#include "Controller.hpp"
//#include "EntityFlag.hpp"
//#include "Components.hpp"
//#include "Animation.hpp"
//#include "Collider.hpp"

#include "ComponentBase.hpp"
#include "SystemBase.hpp"

//TODO I'm not sure if this class should be static... consider that. The question is: would you have more than 1 world per time? If so, then you don't want it static, if no
//then you do want it static

class World
{
public:
    World();
    ~World();
    
//private: TODO maybe make them private and use properties?
    std::vector<unsigned long int> EntitiesComponentsMasks; //defines components held by each entity
    
    std::vector<std::map<unsigned long int, ComponentBase*>> EntitiesComponentsMatrix;
    
    std::map<unsigned long int, SystemBase*> Systems;
    
    //TODO needs to be deleted, legacy stuff before the introduction of generics
    //components arrays
//    std::vector<Acceleration*> Acceleration;
//    std::vector<Appearance*> Appearance;
//    std::vector<Controller*> Controller;
//    std::vector<Velocity*> Velocity;
//    std::vector<EntityFlag*> EntityFlag;
//    std::vector<Collider*> Collider;
//    std::vector<Animation*> Animation;
    
    //not sure the AddSystem has to be kept
//    void AddSystem(System* const system);
//    const System* const GetSystemAtIndex(const int position);
//    const std::vector<System*>& GetAllSystems();
};



#endif /* _WORLD_HPP_ */

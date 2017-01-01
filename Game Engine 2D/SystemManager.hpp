//
//  SystemManager.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _SYSTEM_MANAGER_HPP_
#define _SYSTEM_MANAGER_HPP_

#include "stdafx.h"
#include "World.hpp"
#include "System.hpp"
#include <typeinfo> 

class SystemManager
{
public:
//    SystemManager();
//    ~SystemManager();
    static void Init(World& world);
    static void Terminate(World& world);
    
    static void StartAll(World& world);
    static void ProcessAllInput(World& world, const sf::Event& event);
    static void UpdateAll(World& world);
    static void RenderAll(World& world);
    static void ExitAll(World& world); // TODO THIS SHOULD BE REMOVED, because the world should take care of deleting the refertences to the system objects
    
    template<typename First, typename ...Rest>
    static void AddSystem(World& world, System<First,Rest...>* systemToAdd);
    
private:
        
};


template<typename First, typename ...Rest>
void SystemManager::AddSystem(World& world, System<First,Rest...>* systemToAdd)
{
    if(world.Systems.find(systemToAdd->Id) == world.Systems.end())  //if system never added before
    {
        world.Systems.insert(std::make_pair(systemToAdd->Id, static_cast<SystemBase*>(systemToAdd)));
        
#ifdef LOG_OUTPUT_CONSOLE
        std::stringstream ss;
        ss << "System: " << typeid(systemToAdd).name() << " added with Id: " << systemToAdd->Id << std::endl;
        std::string s = ss.str();
        Utils::PrintDebugLog(__PRETTY_FUNCTION__, s);
#endif
    }
    else
    {
        std::stringstream ss;
        ss << "system " << typeid(systemToAdd).name() << " already added to the selected world!";
        std::string s = ss.str();
        Utils::PrintDebugWarning(__PRETTY_FUNCTION__, s);
    }
    
}

#endif /* _SYSTEM_MANAGER_HPP_ */

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
#include "SystemBase.hpp"

class SystemManager
{
public:
//    SystemManager();
//    ~SystemManager();
    static void Init();
    static void Terminate();
    
    static void StartAll();
    static void ProcessAllInput();
    static void UpdateAll();
    static void RenderAll();
    static void ExitAll();
    
    //not sure the AddSystem has to be kept
    static void AddSystem(SystemBase* const system);
    static const SystemBase* const GetSystemAtIndex(const int position);
    static const std::vector<SystemBase*>& GetAllSystems();
    
private:
    static std::vector<SystemBase*> systems;
//    static void DeleteSystems();
    
};

#endif /* _SYSTEM_MANAGER_HPP_ */

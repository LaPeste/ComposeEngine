//
//  SystemManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "SystemManager.hpp"
#include "SystemBase.hpp"
#include "Movement.hpp"
#include "Renderer.hpp"
#include "Input.hpp"

void SystemManager::Init()
{
    Movement* m = new Movement;
    systems.push_back(m);
    Renderer* r = new Renderer;
    systems.push_back(r);
    Input* i = new Input;
    systems.push_back(i);
}

std::vector<SystemBase*> SystemManager::systems;

void SystemManager::StartAll()
{
    for(std::vector<SystemBase*>::iterator system = systems.begin(); system != systems.end(); ++system)
    {
        (*system)->OnStart();
    }
}

void SystemManager::ProcessAllInput(const sf::Event& event)
{
    for(std::vector<SystemBase*>::iterator system = systems.begin(); system != systems.end(); ++system)
    {
        (*system)->OnInput(event);
    }
}

void SystemManager::UpdateAll()
{
    for(std::vector<SystemBase*>::iterator system = systems.begin(); system != systems.end(); ++system)
    {
        (*system)->OnUpdate();
    }
}

void SystemManager::RenderAll()
{
    for(std::vector<SystemBase*>::iterator system = systems.begin(); system != systems.end(); ++system)
    {
        (*system)->OnRender();
    }
}

void SystemManager::ExitAll()
{
    for(std::vector<SystemBase*>::iterator system = systems.begin(); system != systems.end(); ++system)
    {
        (*system)->OnExit();
        delete(*system);
    }
}

//void SystemManager::DeleteSystems()
//{
//    for(std::vector<SystemBase>::iterator system = systems.begin(); system != systems.end(); ++ system)
//}

/*
 void AddSystem(const SystemBase* const system);
 const SystemBase* const GetSystemAtIndex(const int position) const;
 const std::vector<SystemBase>* const GetAllSystems() const;
*/

void SystemManager::AddSystem(SystemBase* const system)
{
    systems.push_back(system);
}

const SystemBase* const SystemManager::GetSystemAtIndex(const int position)
{
    return systems[position];
}

const std::vector<SystemBase*>& SystemManager::GetAllSystems()
{
    return systems;
}





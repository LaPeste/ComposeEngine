//
//  SystemManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//
#include "SystemManager.hpp"
#include "System.hpp"
#include "Movement.hpp"
#include "Renderer.hpp"
#include "InputSystem.hpp"
#include "Animator.hpp"

void SystemManager::Init(World& world)
{
//    Movement* m = new Movement;
//    systems.push_back(m);
//    Renderer* r = new Renderer;
//    systems.push_back(r);
//    Input* i = new Input;
//    systems.push_back(i);
//    Animator* a = new Animator();
//    systems.push_back(a);
}

void SystemManager::StartAll(World& world)
{
//    for(std::vector<System*>::iterator system = systems.begin(); system != systems.end(); ++system)
    for (auto const & system : world.Systems)
    {
        system.second->OnStart();
    }
}

void SystemManager::ProcessAllInput(World& world, const sf::Event& event)
{
    for (auto const & system : world.Systems)
    {
        system.second->OnInput(event);
    }
}

void SystemManager::UpdateAll(World& world)
{
    for (auto const & system : world.Systems)
    {
        system.second->OnUpdate();
    }
}

void SystemManager::RenderAll(World& world)
{
    for (auto const & system : world.Systems)
    {
        system.second->OnRender();
    }
}

void SystemManager::LateUpdateAll(World& world)
{
	for (auto const & system : world.Systems)
	{
		system.second->OnLateUpdate();
	}
}

void SystemManager::ExitAll(World& world)
{
    for (auto const & system : world.Systems)
    {
        system.second->OnExit();
    }
}

//void SystemManager::DeleteSystems()
//{
//    for(std::vector<System>::iterator system = systems.begin(); system != systems.end(); ++ system)
//}

/*
 void AddSystem(const System* const system);
 const System* const GetSystemAtIndex(const int position) const;
 const std::vector<System>* const GetAllSystems() const;
*/






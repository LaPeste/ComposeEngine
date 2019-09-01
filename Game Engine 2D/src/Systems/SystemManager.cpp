//
//  SystemManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//
#include "Systems/SystemManager.hpp"
#include "Systems/System.hpp"
#include "Systems/Movement.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/Animator.hpp"

void SystemManager::Init(World& world)
{}

void SystemManager::StartAll(World& world)
{
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






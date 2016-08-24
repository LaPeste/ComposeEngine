//
//  Renderer.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Renderer.hpp"
#include "Engine.hpp"
#include "SystemManager.hpp"

Renderer::Renderer() : SystemBase()
{

}

void Renderer::OnStart()
{
    
}

void Renderer::OnRender()
{
    Engine& engine = Engine::GetInstance();
    for(int i = 0; i < engine.World.EntitiesMasks.size(); ++i)
    {
        if((engine.World.EntitiesMasks[i] & RENDERER_MASK) == (RENDERER_MASK))
        {
            Draw(engine.World, i, *engine.GetWindow());
        }
    }
}

void Renderer::OnExit()
{
    
}

void Renderer::Draw(const World& world, const unsigned long entityIndex, sf::RenderWindow& window)
{
    Appearance& appearance = *world.Appearance[entityIndex];
    
    if (appearance.IsSpriteLoaded())
    {
//        if(toAnimate) animator.Animate(sprite); TODO add animator
        
        window.draw(*appearance.GetSprite());
    }
}

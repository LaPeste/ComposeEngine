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

Renderer::Renderer(World& world) : System<Appearance>(world)
{

}

Renderer::~Renderer(){}

void Renderer::OnStart()
{
    
}

void Renderer::OnRender()
{
    Engine& engine = Engine::GetInstance();
    for(int i = 0; i < engine.World.EntitiesComponentsMasks.size(); ++i)
    {
        if((engine.World.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
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
    std::map<unsigned long int, ComponentBase*> entity = world.EntitiesComponentsMatrix[entityIndex];
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);
    
    if (appearance->IsSpriteLoaded())
    {
        window.draw(*appearance->GetSprite());
    }
}

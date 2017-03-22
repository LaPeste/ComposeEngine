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

void Renderer::Render(World& world, const unsigned long int entityIndex)
{
	Draw(world, entityIndex, *Engine::GetInstance().GetWindow());
}


void Renderer::Draw(World& world, const unsigned long entityIndex, sf::RenderWindow& window)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);
    
    if (appearance->IsTextureLoaded())
    {
        window.draw(*appearance->GetSprite());
    }
}

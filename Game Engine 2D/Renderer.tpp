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

template<typename First, typename Second, typename ...Rest>
Renderer<First, Second, Rest...>::Renderer(World& world) : System<First, Second, Rest...>(world)
{

}

template<typename First, typename Second, typename ...Rest>
Renderer<First, Second, Rest...>::~Renderer(){}

template<typename First, typename Second, typename ...Rest>
void Renderer<First, Second, Rest...>::OnStart()
{
    
}

template<typename First, typename Second, typename ...Rest>
void Renderer<First, Second, Rest...>::OnRender()
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

template<typename First, typename Second, typename ...Rest>
void Renderer<First, Second, Rest...>::OnExit()
{
    
}

template<typename First, typename Second, typename ...Rest>
void Renderer<First, Second, Rest...>::Draw(const World& world, const unsigned long entityIndex, sf::RenderWindow& window)
{
    std::map<unsigned long int, ComponentBase*> entity = world.EntitiesComponentsMatrix[entityIndex];
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);
    
    if (appearance->IsSpriteLoaded())
    {
        window.draw(*appearance->GetSprite());
    }
}

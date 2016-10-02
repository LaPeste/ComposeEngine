//
//  Position.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "TransforUtils.hpp"
#include "Appearance.hpp"

const sf::Vector2f& TransformUtils::GetPosition(const World& world, unsigned const long entityIndex)
{
    Appearance* appearance = world.Appearance[entityIndex];
    
    if(appearance == nullptr)
    {
        Utils::PrintDebugError("Position::GetPosition", "The component appearance for the entity " +  std::to_string(entityIndex) + " is null! Abort!");
        std::exit(EXIT_FAILURE);
    }
    return appearance->GetSprite()->getPosition();
}

void TransformUtils::SetPosition(const World& world, unsigned const long entityIndex, sf::Vector2f position)
{
    Appearance* appearance = world.Appearance[entityIndex];
    if(appearance == nullptr)
    {
        Utils::PrintDebugError("Position::GetPosition", "The component appearance for the entity " +  std::to_string(entityIndex) + " is null! Abort!");
        std::exit(EXIT_FAILURE);
    }
    appearance->GetSprite()->setPosition(position.x, position.y);
}
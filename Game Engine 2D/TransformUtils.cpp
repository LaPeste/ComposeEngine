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
    std::map<unsigned long int, ComponentBase*> entityComponents = world.EntitiesComponentsMatrix[entityIndex];
    Appearance* appearance = static_cast<Appearance*>(entityComponents[Component<Appearance>::Id]);
    if(appearance == nullptr)
    {
        std::stringstream ss;
        ss << "The component " << typeid(appearance).name() << " for the entity " <<  std::to_string(entityIndex) << " is null! Abort!" << std::endl;
        std::string s = ss.str();
        Utils::PrintDebugError(__PRETTY_FUNCTION__, s);
        std::exit(EXIT_FAILURE);
    }
    return appearance->GetSprite()->getPosition();
}

void TransformUtils::SetPosition(const World& world, unsigned const long entityIndex, sf::Vector2f position)
{
    std::map<unsigned long int, ComponentBase*> entityComponents = world.EntitiesComponentsMatrix[entityIndex];
    Appearance* appearance = static_cast<Appearance*>(entityComponents[Component<Appearance>::Id]);
    if(appearance == nullptr)
    {
        std::stringstream ss;
        ss << "The component " << typeid(appearance).name() << " for the entity " <<  std::to_string(entityIndex) << " is null! Abort!" << std::endl;
        std::string s = ss.str();
        Utils::PrintDebugError(__PRETTY_FUNCTION__, s);
        std::exit(EXIT_FAILURE);
    }
    appearance->GetSprite()->setPosition(position.x, position.y);
}

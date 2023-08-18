//
//  Appearance.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Components/Appearance.hpp"
#include "Components/Transform.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"
#include "Animations/Animation.hpp"

Appearance::Appearance(World& world, const unsigned long int entityIndex, std::string spritePath, sf::IntRect initialAppearance) :
	Component(world, entityIndex), m_sprite(nullptr), texture(nullptr)
{
	std::string methodName = _FUNCTION_NAME_;
    Appearance::SpritePath = spritePath;
    texture = new sf::Texture;
    
    if (!texture->loadFromFile(Appearance::SpritePath))
    {
        Utils::PrintDebugError(methodName, "impossible to load texture from " + spritePath + "!");
        assert(IsTextureLoaded()); //you do this because you can't return a value from a constructor!!
    }
    else
    {
        m_sprite = std::make_unique<sf::Sprite>();
        m_sprite->setTexture(*texture);
        
        if(m_sprite->getTexture() != nullptr)
        {
#ifdef INTERNAL_DEBUG
            Utils::PrintDebugLog(methodName, "texture " + SpritePath + " correctly loaded!");
#endif
        }
        else
        {
            Utils::PrintDebugError(methodName, "texture " + SpritePath + " not correctly loaded!");
            
        }

		// if initialAppearance isn't a default rect, apply it to set only a part of the tecture as sprite
		if (initialAppearance != sf::IntRect())
		{
			m_sprite->setTextureRect(initialAppearance);
		}
    }

	//set position written in a Transform Component if it exists
	if (Entity::HasComponent(world, entityIndex, Transform::Id))
	{
		std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
		Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

		if (transform != nullptr)
		{
			m_sprite->setPosition(transform->GetPosition());
		}
	}
}

Appearance::~Appearance()
{
    delete texture;
    
#if DEBUG
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugLog(methodName, "sprite and texture memory freed");
#endif
}

sf::Sprite* const Appearance::GetSprite() const
{
    if(m_sprite != nullptr)
    {
        return m_sprite.get();
    }
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugError(methodName, "you are trying to get the sprite, but it is not loaded yet!");
    return nullptr;
}

void Appearance::SetSprite(std::unique_ptr<const sf::Sprite>& m_sprite)
{
    m_sprite = std::move(m_sprite);
}

bool Appearance::IsTextureLoaded() const
{
	return m_sprite->getTexture() != nullptr;
}

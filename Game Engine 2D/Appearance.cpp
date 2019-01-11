//
//  Appearance.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Appearance.hpp"
#include "Transform.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"

Appearance::Appearance(World& world, const unsigned long int entityIndex, std::string spritePath) : Component(world, entityIndex)
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
        sprite = new sf::Sprite;
        sprite->setTexture(*texture);
        
        if(sprite->getTexture() != nullptr)
        {
#ifdef DEBUG
            Utils::PrintDebugLog(methodName, "texture " + SpritePath + " correctly loaded!");
#endif
        }
        else
        {
            Utils::PrintDebugError(methodName, "texture " + SpritePath + " not correctly loaded!");
            
        }
    }

	//set position written in a Transform Component if it exists
	if (Entity::HasComponent(world, entityIndex, Transform::Id))
	{
		std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
		Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

		if (transform != nullptr)
		{
			sprite->setPosition(transform->GetPosition());
		}
	}
}

Appearance::~Appearance()
{
    delete texture;
    delete sprite;
    
#if DEBUG
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugLog(methodName, "sprite and texture memory freed");
#endif
}

sf::Sprite* const Appearance::GetSprite() const
{
    if(sprite != nullptr)
    {
        return sprite;
    }
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugError(methodName, "you are trying to get the sprite, but it is not loaded yet!");
    return nullptr;
}

void Appearance::SetSprite(sf::Sprite* const sprite)
{
    Appearance::sprite = sprite;
}

bool Appearance::IsTextureLoaded() const
{
	return sprite->getTexture() != nullptr;
}

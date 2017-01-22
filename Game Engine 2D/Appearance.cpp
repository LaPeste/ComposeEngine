//
//  Appearance.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Appearance.hpp"

Appearance::Appearance(std::string spritePath) : Component()
{
	std::string methodName = _FUNCION_NAME_;
    Appearance::SpritePath = spritePath;
    texture = new sf::Texture;
    if (!texture->loadFromFile(Appearance::SpritePath)) //TODO load only a subretangle of the whole sprite. Check method signature to see how
    {
        Utils::PrintDebugError(methodName, "impossible to load texture from " + spritePath + "!");
        assert(IsSpriteLoaded()); //you do this because you can't return a value from a constructor!!
    }
    else
    {
        sprite = new sf::Sprite;
        sprite->setTexture(*texture);
        
        if(sprite->getTexture() != nullptr)
        {
//            isLoaded = true;
#ifdef DEBUG
            Utils::PrintDebugLog(methodName, "texture " + SpritePath + " correctly loaded!");
#endif
        }
        else
        {
//            isLoaded = false;
            Utils::PrintDebugError(methodName, "texture " + SpritePath + " not correctly loaded!");
            
        }
    }
}

Appearance::~Appearance()
{
    delete texture;
    delete sprite;
    
#if DEBUG
	std::string methodName = _FUNCION_NAME_;
    Utils::PrintDebugLog(methodName, "sprite and texture memory freed");
#endif
}

sf::Sprite* const Appearance::GetSprite() const
{
    if(IsSpriteLoaded())
    {
        return sprite;
    }
	std::string methodName = _FUNCION_NAME_;
    Utils::PrintDebugError(methodName, "you are trying to get the sprite, but it is not loaded yet!");
    return nullptr;
}

void Appearance::SetSprite(sf::Sprite* const sprite)
{
    Appearance::sprite = sprite;
}

bool Appearance::IsSpriteLoaded() const
{
    return sprite->getTexture() != nullptr;
}

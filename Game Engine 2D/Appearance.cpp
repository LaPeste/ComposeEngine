//
//  Appearance.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Appearance.hpp"

Appearance::Appearance(sf::Sprite* const sprite) : sprite(sprite)
{
    
}

Appearance::Appearance(std::string spritePath)
{
#ifdef _WIN32
        std::string loadPath = "images/" + spritePath;
#elif __APPLE__ && __MACH__
        std::string loadPath = resourcePath() + spritePath;
        //TODO #should do the linux version
#endif
    Appearance::SpritePath = loadPath;
    texture = new sf::Texture;
    if (!texture->loadFromFile(Appearance::SpritePath)) //TODO load only a subretangle of the whole sprite. Check method signature to see how
    {
        Utils::PrintDebugError("Appearance::Appearance", "impossible to load texture from " + spritePath + "!");
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
            Utils::PrintDebugLog("Appearance::Appearance", "texture correctly loaded!");
#endif
        }
        else
        {
//            isLoaded = false;
            Utils::PrintDebugError("Appearance::Appearance", "texture not correctly loaded!");
            
        }
    }
}

Appearance::~Appearance()
{
    delete texture;
    delete sprite;
    
#if DEBUG
    Utils::PrintDebugLog("~Appearance", "sprite and texture memory freed");
#endif
}

sf::Sprite* const Appearance::GetSprite() const
{
    if(IsSpriteLoaded())
    {
        return sprite;
    }
    Utils::PrintDebugError("Appearance::GetSprite", "you are trying to get the sprite, but it is not loaded yet!");
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
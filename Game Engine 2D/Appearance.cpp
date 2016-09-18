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

Appearance::Appearance(std::string spritePath, int spriteMaxFrame, float animationFrameRate, bool reverseAnimation,
                       float spriteBeginningX, float spriteBeginningY, float spriteWidth, float spriteHeight) :
    spriteMaxFrame(spriteMaxFrame), animationFrameRate(animationFrameRate), reverseAnimation(reverseAnimation)
//    spriteBeginningX(spriteBeginningX), spriteBeginningY(spriteBeginningY), spriteWidth(spriteWidth), spriteHeight(spriteHeight)
{
#ifdef _WIN32
        std::string loadPath = "images/" + spritePath;
#elif __APPLE__ && __MACH__
        std::string loadPath = resourcePath() + spritePath;
        //TODO #should do the linux version
#endif
    Appearance::spritePath = loadPath;
    texture = new sf::Texture;
    if (!texture->loadFromFile(Appearance::spritePath)) //TODO load only a subretangle of the whole sprite. Check method signature to see how
    {
//        isLoaded = false;
        Utils::PrintDebugError("Appearance::Appearance", "impossible to load texture from " + spritePath + "!");
        assert(IsSpriteLoaded()); //you do this because you can't return a value from a constructor!!
    }
    else
    {
        sprite = new sf::Sprite;
        sprite->setTexture(*texture);
        
        //set subTexture
        if(texture->getSize().x > spriteWidth || texture->getSize().y > spriteHeight) //set subtexture only if needed, based on parameters
        {
            sf::Rect<int> subTextureRect(spriteBeginningX, spriteBeginningY, spriteWidth, spriteHeight);
            sprite->setTextureRect(subTextureRect);
//            SetSubTexture(startingLeft, startingTop, width, height);
        }
        
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
    
    collisionPoints[0] = sf::Vector2f{0, 0};
    collisionPoints[1] = sf::Vector2f{sprite->getGlobalBounds().width, 0};
    collisionPoints[2] = sf::Vector2f{0, sprite->getGlobalBounds().height};
    collisionPoints[3] = sf::Vector2f{sprite->getGlobalBounds().width, sprite->getGlobalBounds().height};
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
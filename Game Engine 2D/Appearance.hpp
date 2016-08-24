//
//  Appearance.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _APPEARANCE_HPP_
#define _APPEARANCE_HPP_

#include "stdafx.h"

class Appearance
{
public:
    Appearance(); //dummy appearance, needed to make initialization of world faster
    Appearance(std::string spritePath, int spriteMaxFrame, float animationFrameRate, bool reverseAnimation,
               float spriteBeginningX, float spriteBeginningY, float spriteWidth, float spriteHeight);
    ~Appearance();
    
    //TODO maybe make them private and make them setable only from constructor?
    std::string spritePath;
    int spriteMaxFrame;
    float animationFrameRate;
    bool reverseAnimation;
//    float spriteBeginningX;
//    float spriteBeginningY;
//    float spriteWidth;
//    float spriteHeight;
    
    const sf::Sprite* const GetSprite() const; //returns null if not loaded
    bool IsSpriteLoaded() const;
    
private:
    sf::Sprite* sprite;
    sf::Texture* texture;
    
};

#endif /* _APPEARANCE_HPP_ */

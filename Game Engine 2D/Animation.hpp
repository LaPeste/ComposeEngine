//
//  Animation.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _ANAMATION_HPP_
#define _ANAMATION_HPP_

#include "stdafx.h"
#include "Component.hpp"

//struct for POD C-style
struct AnimationData
{
public:
    AnimationData(const sf::Vector2f& startingPos, const sf::Vector2f& spaceBetweenSprite, bool verticalMovement, bool reverseAnimation, float spriteWidth, float spriteHeight, int maxFrame, int frameRate);

    sf::Vector2f StartingPos;
    sf::Vector2f SpaceBetweenSprite;
    bool VerticalMovement; //if true the sprite sequence develops vertically, horizzontaly otherwise.
    bool FlipSprite; //if true the sprite will be flipped. If false, it'll be left as it is. Flipping a sprite is useful when an animation needs to be performed in opposite direction
    bool ReverseAnimation; //if true the animation follow this order 0,1,2...end and end...2,1,0. If false, 0,1,2...end and again 0,1,2...end
    bool Ahead; //used by the animator during the reversal of the animation to keep track what direction it has to follow on the sprite sheet
    int CurrentFrame;
    float SpriteWidth, SpriteHeight;
    int MaxFrame, FrameRate;
};

enum class AnimationState : char
{
    IDLE = 0,
    WALKING,
    RUNNING,
    JUMPING,
    ATTACKING
};
    
    
    
    
//Holds all the info of the animation it represents
    
class Animation : public Component<Animation>
{
public:
    Animation(World& world, const unsigned long int entityIndex, const AnimationState& intialAnimationState, std::map<AnimationState, AnimationData*>& animationMap, bool toAnimate);
    ~Animation();
    
    sf::Clock Clock;
    bool ToAnimate; //when to animate if pressed a direction
    AnimationState CurrentAnimationState;
    std::map<AnimationState, AnimationData*> AnimationMap;
    
private:
    
};

#endif /* _ANAMATION_HPP_ */

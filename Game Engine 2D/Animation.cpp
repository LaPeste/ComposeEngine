//
//  Animation.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Animation.hpp"


Animation::Animation(World& world, const unsigned long int entityIndex, const AnimationState& intialAnimationState, std::map<AnimationState, AnimationData*>& animationMap, bool toAnimate) :
    AnimationMap(animationMap), CurrentAnimationState(intialAnimationState), ToAnimate(toAnimate), FlipAnimation(false), Clock(), Component(world, entityIndex)
{

}

Animation::~Animation()
{
    for(auto& animationEntry : AnimationMap)
    {
        delete animationEntry.second;
    }
}

AnimationData::AnimationData(const sf::Vector2f& startingPos,
                             const sf::Vector2f& spaceBetweenSprite, bool verticalMovement, bool reverseAnimation,
                             float spriteWidth, float spriteHeight, int maxFrame, int frameRate) :
StartingPos(startingPos), SpaceBetweenSprite(spaceBetweenSprite), VerticalMovement(verticalMovement), FlipSprite(false), ReverseAnimation(reverseAnimation), CurrentFrame(0),
SpriteWidth(spriteWidth), SpriteHeight(spriteHeight), MaxFrame(maxFrame), Ahead(false), FrameRate(frameRate) {}

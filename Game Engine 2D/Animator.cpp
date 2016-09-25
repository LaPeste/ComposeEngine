//
//  Animator.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Animator.hpp"
#include "Animation.hpp"
#include "Engine.hpp"

Animator::Animator(){}

void Animator::OnUpdate()
{
    
    World& world = Engine::GetInstance().World;
    
    for(int i = 0; i < world.EntitiesMasks.size(); ++i)
    {
        if((world.EntitiesMasks[i] & ANIMATION_MASK) == (ANIMATION_MASK))
        {
            Animate(world, i);
        }
        
    }
}

void Animator::Animate(const World& world, const unsigned long entityIndex)
{
    Animation& animation = *world.Animation[entityIndex];
    Appearance& appearance = *world.Appearance[entityIndex];
    
    if(animation.ToAnimate)
    {
        if(animation.AnimationMap.find(animation.CurrentAnimationState) == animation.AnimationMap.end())
        {
            Utils::PrintDebugWarning("Appearance", "No found for the current animation state, setting the whole sprite as to be rendered");
        }
        else
        {
            AnimationData& currentAnimData = animation.AnimationMap[animation.CurrentAnimationState];
            sf::Rect<int> finalRect(currentAnimData.StartingPos.x + currentAnimData.CurrentFrame * (appearance.GetSprite()->getLocalBounds().width + currentAnimData.SpaceBetweenSprite.x),
                                    currentAnimData.StartingPos.y,
                                    currentAnimData.SpriteWidth,
                                    currentAnimData.SpriteHeight);
            
            appearance.GetSprite()->setTextureRect(finalRect); //this is the core of the whole method
            
            if(animation.Clock.getElapsedTime().asMilliseconds() > currentAnimData.FrameRate)
            {
                animation.Clock.restart();

                if(currentAnimData.ReverseAnimation)
                {
                    if(currentAnimData.Ahead)
                    {
                        currentAnimData.CurrentFrame++;
                        if(currentAnimData.CurrentFrame >= currentAnimData.MaxFrame)
                        {
                            currentAnimData.CurrentFrame = currentAnimData.MaxFrame - 1;
                            currentAnimData.Ahead = false;
                        }
                    }
                    else //if(!animation.Ahead)
                    {
                        currentAnimData.CurrentFrame--;
                        if(currentAnimData.CurrentFrame < 0)
                        {
                            currentAnimData.CurrentFrame = 1;
                            currentAnimData.Ahead = true;
                        }
                    }
                }
                else
                {
                    currentAnimData.CurrentFrame++;
                    if(currentAnimData.CurrentFrame >= currentAnimData.MaxFrame)
                    {
                        currentAnimData.CurrentFrame = 0;
                    }
                }
            }

            if(currentAnimData.FlipSprite)
            {
                appearance.GetSprite()->setOrigin({ appearance.GetSprite()->getLocalBounds().width, 0 });
                appearance.GetSprite()->setScale({-1, 1 });
            }
            else
            {
                appearance.GetSprite()->setOrigin({ 0, 0 });
                appearance.GetSprite()->setScale(1, 1);
            }
        }
    }
}
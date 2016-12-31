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

template<typename First, typename Second, typename ...Rest>
Animator<First, Second, Rest...>::Animator(World& world) : System<First, Second, Rest...>(world){}

template<typename First, typename Second, typename ...Rest>
Animator<First, Second, Rest...>::~Animator(){}

template<typename First, typename Second, typename ...Rest>
void Animator<First, Second, Rest...>::OnUpdate()
{
    
    World& world = Engine::GetInstance().World;
    
    for(int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
    {
        if((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
        {
            Animate(world, i);
        }
        
    }
}

template<typename First, typename Second, typename ...Rest>
void Animator<First, Second, Rest...>::Animate(const World& world, const unsigned long entityIndex)
{
    std::map<unsigned long int, ComponentBase*> entity = world.EntitiesComponentsMatrix[entityIndex];
    Animation* animation = static_cast<Animation*>(entity[Component<Animation>::Id]);
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);

    if(animation->ToAnimate)
    {
        if(animation->AnimationMap.find(animation->CurrentAnimationState) == animation->AnimationMap.end())
        {
            Utils::PrintDebugWarning("Appearance", "No found for the current animation state, setting the whole sprite as to be rendered");
        }
        else
        {
            AnimationData* currentAnimData = animation->AnimationMap[animation->CurrentAnimationState];
            sf::Rect<int> finalSpriteRect;
            if(currentAnimData->VerticalMovement)
            {
                finalSpriteRect.left = currentAnimData->StartingPos.x;
                finalSpriteRect.top = currentAnimData->StartingPos.y + currentAnimData->CurrentFrame * (appearance->GetSprite()->getLocalBounds().height + currentAnimData->SpaceBetweenSprite.y);
            }
            else
            {
                finalSpriteRect.left = currentAnimData->StartingPos.x + currentAnimData->CurrentFrame * (appearance->GetSprite()->getLocalBounds().width + currentAnimData->SpaceBetweenSprite.x);
                finalSpriteRect.top = currentAnimData->StartingPos.y;
            }
            finalSpriteRect.width = currentAnimData->SpriteWidth;
            finalSpriteRect.height = currentAnimData->SpriteHeight;
            
            appearance->GetSprite()->setTextureRect(finalSpriteRect); //this is the core of the whole method
            
            if(animation->Clock.getElapsedTime().asMilliseconds() > currentAnimData->FrameRate)
            {
                animation->Clock.restart();

                if(currentAnimData->ReverseAnimation)
                {
                    if(currentAnimData->Ahead)
                    {
                        currentAnimData->CurrentFrame++;
                        if(currentAnimData->CurrentFrame >= currentAnimData->MaxFrame)
                        {
                            currentAnimData->CurrentFrame = currentAnimData->MaxFrame - 1;
                            currentAnimData->Ahead = false;
                        }
                    }
                    else //if(!animation.Ahead)
                    {
                        currentAnimData->CurrentFrame--;
                        if(currentAnimData->CurrentFrame < 0)
                        {
                            currentAnimData->CurrentFrame = 1;
                            currentAnimData->Ahead = true;
                        }
                    }
                }
                else
                {
                    currentAnimData->CurrentFrame++;
                    if(currentAnimData->CurrentFrame >= currentAnimData->MaxFrame)
                    {
                        currentAnimData->CurrentFrame = 0;
                    }
                }
            }

            if(currentAnimData->FlipSprite)
            {
                appearance->GetSprite()->setOrigin({ appearance->GetSprite()->getLocalBounds().width, 0 });
                appearance->GetSprite()->setScale({-1, 1 });
            }
            else
            {
                appearance->GetSprite()->setOrigin({ 0, 0 });
                appearance->GetSprite()->setScale(1, 1);
            }
        }
    }
}

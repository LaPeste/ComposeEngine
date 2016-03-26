#include "Animator.h"

Animator::Animator(int spriteMaxFrame, int animationFrameRate, bool reverseAnimation) :
    currentFrame(0),
    ahead(true)
{
    Animator::maxFrame = spriteMaxFrame;
    Animator::animationFrameRate = animationFrameRate;
    Animator::reverseAnimation = reverseAnimation;
}

Animator::~Animator()
{
    
}

int Animator::GetCurrentFrame()
{
    return currentFrame;
}

const sf::Rect<int> Animator::Animate()
{
    sf::Rect<int> finalRect(Constants::PLAYER_SPRITE_STARTING_X + currentFrame * (Constants::PLAYER_WIDTH + Constants::SPACE_BETWEEN_SPRITE_X),
                            Constants::PLAYER_SPRITE_STARTING_Y,
                            Constants::PLAYER_WIDTH,
                            Constants::PLAYER_HEIGHT);
    if(clock.getElapsedTime().asMilliseconds() > animationFrameRate)
    {
        clock.restart();
        
        if(reverseAnimation)
        {
            if(ahead)
            {
                currentFrame++;
                if(currentFrame >= maxFrame)
                {
                    currentFrame = maxFrame - 1;
                    ahead = false;
                }
            }
            if(!ahead)
            {
                currentFrame--;
                if(currentFrame < 0)
                {
                    currentFrame = 1;
                    ahead = true;
                }
            }
        }
        else
        {
            currentFrame++;
            if(currentFrame >= maxFrame)
            {
                currentFrame = 0;
            }
        }
    }
    return finalRect;
}
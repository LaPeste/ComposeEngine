#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "stdafx.h"

//This class assumes that the sprite set is horizontally developed

class Animator
{
    
public:
    Animator(int spriteMaxFrame, int animationFrameRate, bool reverseAnimation);
    ~Animator();
    
    int GetCurrentFrame() const;
    void Animate(sf::Sprite& sprite);
    void FlipSprite(bool toFlip); //to similate walk right or left
    void AnimateSprite(bool toAnimate);
    
private:
    int currentFrame;
    int maxFrame;
    int animationFrameRate;
    bool reverseAnimation;
    bool ahead;
    sf::Clock clock;
    bool flipSprite; //orientation for the movements
    bool toAnimate; //when to animate if pressed a direction
};

#endif
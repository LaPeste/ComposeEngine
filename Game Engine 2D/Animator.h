#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "stdafx.h"

//This class assumes that the sprite set is horizontally developed

class Animator
{
    
public:
    Animator(int spriteMaxFrame, int animationFrameRate, bool reverseAnimation);
    ~Animator();
    
    int GetCurrentFrame();
    const sf::Rect<int> Animate();
    
private:
    int currentFrame;
    int maxFrame;
    int animationFrameRate;
    bool reverseAnimation;
    bool ahead;
    sf::Clock clock;
};

#endif
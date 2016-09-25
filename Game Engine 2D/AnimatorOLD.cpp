//#include "Animator.hpp"
//
//Animator::Animator(int spriteMaxFrame, int animationFrameRate, bool reverseAnimation) :
//    currentFrame(0),
//    ahead(true),
//    flipSprite(false)
//{
//    Animator::maxFrame = spriteMaxFrame;
//    Animator::animationFrameRate = animationFrameRate;
//    Animator::reverseAnimation = reverseAnimation;
//}
//
//Animator::~Animator()
//{
//    
//}
//
//int Animator::GetCurrentFrame() const
//{
//    return currentFrame;
//}
//
//void Animator::Animate(sf::Sprite& sprite)
//{
//    if(toAnimate)
//    {
//        sf::Rect<int> finalRect(Constants::PLAYER_SPRITE_STARTING_X + currentFrame * (Constants::PLAYER_WIDTH + Constants::SPACE_BETWEEN_SPRITE_X),
//                                Constants::PLAYER_SPRITE_STARTING_Y,
//                                Constants::PLAYER_WIDTH,
//                                Constants::PLAYER_HEIGHT);
//        if(clock.getElapsedTime().asMilliseconds() > animationFrameRate)
//        {
//            clock.restart();
//            
//            if(reverseAnimation)
//            {
//                if(ahead)
//                {
//                    currentFrame++;
//                    if(currentFrame >= maxFrame)
//                    {
//                        currentFrame = maxFrame - 1;
//                        ahead = false;
//                    }
//                }
//                if(!ahead)
//                {
//                    currentFrame--;
//                    if(currentFrame < 0)
//                    {
//                        currentFrame = 1;
//                        ahead = true;
//                    }
//                }
//            }
//            else
//            {
//                currentFrame++;
//                if(currentFrame >= maxFrame)
//                {
//                    currentFrame = 0;
//                }
//            }
//        }
//        
//        sprite.setTextureRect(finalRect);
//        
//        if(flipSprite)
//        {
//            sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
//            sprite.setScale({-1, 1 });
//        }
//        else
//        {
//            sprite.setOrigin({ 0, 0 });
//            sprite.setScale(1, 1);
//        }
//    }
//}
//
//void Animator::FlipSprite(bool toFlip)
//{
//    Animator::flipSprite = toFlip;
//}
//
//void Animator::AnimateSprite(bool toAnimate)
//{
//    Animator::toAnimate = toAnimate;
//}
#include "stdafx.h"
#include "Player.h"
#include "Engine.h"
#include "FPS.h"
#include "ResourcePath.hpp" // Here is a small helper for you ! Have a look.

#define elapsedTime()(Engine::GetInstance().Clock().getElapsedTime - timeSinceLastDrawnFrame)

Player::Player(bool toAnimate) :
	velocity(0),
	maxVelocity(60),
	speed(Constants::SPEED),
	MoveLeft(false),
	MoveRight(false),
    GameObject(toAnimate, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE, Constants::REVERSE_ANIMATION, Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y)
{
    
#ifdef _WIN32
    std::string loadPath = "images/" + Constants::PLAYER_SPRITE_NAME;
#elif __APPLE__ && __MACH__
    std::string loadPath = resourcePath() + Constants::PLAYER_SPRITE_NAME;
//#should do the linux version
#endif
    
    GameObject::Load(loadPath, Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
    assert(IsLoaded()); //you do this because you can't return a value from a constructor!!
	GetSprite().setPosition(60, 768/2);
}

Player::~Player()
{

}

void Player::Update()
{
    UpdatePosition(); //base on inputs
}

void Player::Draw(sf::RenderWindow& rw)
{
	GameObject::Draw(rw);
}

float Player::GetVelocity() const
{
	return velocity;
}

void Player::UpdatePosition()
{
    if(MoveLeft)
    {
        if(toAnimate)
        {
            animator.FlipSprite(true);
            animator.AnimateSprite(true);
        }
        if((posX - Constants::PLAYER_STEP_SIZE) >= 0)
        {
            posX -= Constants::PLAYER_STEP_SIZE * FPS::GetSpeedFactor();
        }
    }
    else if(MoveRight)
    {
        if(toAnimate)
        {
            animator.FlipSprite(false);
            animator.AnimateSprite(true);
        }
        if((posX + Constants::PLAYER_STEP_SIZE + Constants::PLAYER_WIDTH) <= Constants::SCREEN_WIDTH)
        {
            posX += Constants::PLAYER_STEP_SIZE * FPS::GetSpeedFactor();
        }
    }
    else if(Jump)
    {
        //TODO
    }
    else if(Crouch)
    {
        //TODO
    }
    else
    {
        animator.AnimateSprite(false);
    }
        
}


/*** THEORY ****

If the argument expression of this macro with functional form compares equal to zero (i.e., the expression is false),
 message is written to the standard error device and abort is called, terminating the program execution.

 */
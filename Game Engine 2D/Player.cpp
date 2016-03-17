#include "stdafx.h"
#include "Player.h"
#include "Constans.h"
#include "Engine.h"

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

#define elapsedTime()(Engine::GetInstance().Clock().getElapsedTime - timeSinceLastDrawnFrame)

Player::Player() :
	velocity(0),
	maxVelocity(60),
	speed(Constants::SPEED),
	MoveLeft(false),
	MoveRight(false)
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

}

void Player::Draw(sf::RenderWindow& rw)
{
	GameObject::Draw(rw);
}

float Player::GetVelocity()
{
	return velocity;
}

void Player::OnKeyDown(sf::Event::KeyEvent input)
{
	
}

//void Player::Crouch()
//{
//
//}
//
//void Player::GoLeft()
//{
//	if (velocity > 0)
//	{
//		velocity -= speed;
//	}
//	else
//	{
//		velocity = 0;
//	}
//
//
//	sf::Vector2f pos = GetPosition();
//	float halfSprite = GetSprite().getTextureRect().width / 2;
//	if (pos.x < 0 || pos.x + halfSprite < 0)
//	{
//		velocity = 0;
//	}
//	GetSprite().move(velocity * elapsedTime(), 0);
//}
//
//void Player::OnMove(float xMove, float yMove)
//{
//	
//}
//
//void Player::GoRight()
//{
//	if (velocity < maxVelocity)
//	{
//		velocity += speed;
//	}
//	else
//	{
//		velocity = maxVelocity;
//	}
//
//	sf::Vector2f pos = GetPosition();
//	float halfSprite = GetSprite().getTextureRect().width / 2;
//	if (pos.x > Constants::SCREEN_WIDTH || pos.x + halfSprite > Constants::SCREEN_WIDTH)
//	{
//		velocity = 0;
//	}
//	GetSprite().move(velocity * elapsedTime(), 0);
//}
//
//void Player::Jump()
//{
//
//}




/*** THEORY ****

If the argument expression of this macro with functional form compares equal to zero (i.e., the expression is false),
 message is written to the standard error device and abort is called, terminating the program execution.

 */
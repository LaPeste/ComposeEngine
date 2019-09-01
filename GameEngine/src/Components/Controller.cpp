//
//  Controller.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Components/Controller.hpp"
#include "Events/InputEvent.hpp"
#include "Components/Velocity.hpp"
#include "Events/EventManager.hpp"

Controller::Controller(World& world, const unsigned long int entityIndex) : moveRight(false), moveLeft(false), crouch(false), wantToJump(false), jumping(false), freeFalling(false),
Component(world, entityIndex)
{
    
}

Controller::~Controller() {}

bool Controller::GetMoveRight() const
{
	return moveRight;
}

bool Controller::GetMoveLeft() const
{
	return moveLeft;
}

bool Controller::GetCrouch() const
{
	return crouch;
}

bool Controller::CanJump() const
{
	return !IsJumping();
}

bool Controller::WantToJump() const
{
	return wantToJump;
}

bool Controller::IsJumping() const
{
	return jumping;
}

bool Controller::IsFreeFalling() const
{
	return freeFalling;
}

void Controller::SetWantToJump(bool wantToJump)
{
	if (!wantToJump || (wantToJump && !CanJump()))	//to avoid weird behaviours
	{
		this->wantToJump = false;
	}
	else
	{
		this->wantToJump = true;
	}
}

void Controller::SetJumping(bool jumping)
{
	this->jumping = jumping;
}

void Controller::SetMoveLeft(bool moveLeft)
{
	if (this->moveLeft != moveLeft)	//avoid to trigger events if nothing has changed
	{
		if (moveLeft) EventManager::QueueEvent(new InputEvent(InputEventType::LEFT_DOWN, entityIndex));
		else EventManager::QueueEvent(new InputEvent(InputEventType::LEFT_UP, entityIndex));

		this->moveLeft = moveLeft;
	}
}

void Controller::SetMoveRight(bool moveRight)
{
	if (this->moveRight != moveRight) //avoid to trigger events if nothing has changed
	{
		if (moveRight) EventManager::QueueEvent(new InputEvent(InputEventType::RIGHT_DOWN, entityIndex));
		else EventManager::QueueEvent(new InputEvent(InputEventType::RIGHT_UP, entityIndex));

		this->moveRight = moveRight;
	}
}

void Controller::SetCrouch(bool crouch)
{
	if (this->crouch != crouch)	//avoid to trigger events if nothing has changed
	{
		if (crouch) EventManager::QueueEvent(new InputEvent(InputEventType::CROUCH_DOWN, entityIndex));
		else EventManager::QueueEvent(new InputEvent(InputEventType::CROUCH_UP, entityIndex));
		this->crouch = crouch;
	}
}

//void Controller::SetCanJump(bool canJump)
//{
//	this->canJump = canJump;
//}

void Controller::SetFreeFalling(bool freeFalling)
{
	if (!IsJumping() && !this->freeFalling && freeFalling) //free falling starts if not jumping
	{
		EventManager::QueueEvent(new InputEvent(InputEventType::FREE_FALLING_START, entityIndex));
	}
	else if(this->freeFalling && !freeFalling)
	{
		EventManager::QueueEvent(new InputEvent(InputEventType::FREE_FALLING_STOP, entityIndex));
	}

	if (!freeFalling) SetJumping(false); //a jump, if started, ends when free falling ends

	this->freeFalling = freeFalling;
}
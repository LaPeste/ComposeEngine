//
//  Controller.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Controller.hpp"
#include "InputEvent.hpp"
#include "Velocity.hpp"

Controller::Controller(World& world, const unsigned long int entityIndex) : moveRight(false), moveLeft(false), crouch(false), currentlyInTheAir(false), canJump(false),
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

bool Controller::GetCanJump() const
{
	return canJump;
}

bool Controller::IsJumping() const
{
	return currentlyInTheAir;
}

void Controller::SetMoveLeft(bool moveLeft)
{
	if(moveLeft) EventManager::QueueEvent(new InputEvent(InputEventType::LEFT_DOWN));
	else EventManager::QueueEvent(new InputEvent(InputEventType::LEFT_UP));

	this->moveLeft = moveLeft;
}

void Controller::SetMoveRight(bool moveRight)
{
	if (moveRight) EventManager::QueueEvent(new InputEvent(InputEventType::RIGHT_DOWN));
	else EventManager::QueueEvent(new InputEvent(InputEventType::RIGHT_UP));

	this->moveRight = moveRight;
}

void Controller::SetCrouch(bool crouch)
{
	if (crouch) EventManager::QueueEvent(new InputEvent(InputEventType::CROUCH_DOWN));
	else EventManager::QueueEvent(new InputEvent(InputEventType::CROUCH_UP));
	this->crouch = crouch;
}

void Controller::SetCanJump(bool canJump)
{
	this->canJump = canJump;
}

void Controller::SetIfJumping(bool jumping)
{
	if (currentlyInTheAir && !jumping)
	{
		EventManager::QueueEvent(new InputEvent(InputEventType::JUMP_STOP));
	}
	currentlyInTheAir = jumping;
}

bool Controller::Jump(World& world, const unsigned long entityIndex)
{
	std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
	Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);
	Velocity* velocity = static_cast<Velocity*>(entity[Component<Velocity>::Id]);

	if (!controller->GetCanJump()) return false;
	
	EventManager::QueueEvent(new InputEvent(InputEventType::JUMP_START));

	velocity->SpeedY = -velocity->MaxSpeedY;
	return true;
}
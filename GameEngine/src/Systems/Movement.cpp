//
//  Movement.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Systems/Movement.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "FPS.hpp"
#include "Collisions/CollisionDetectionUtils.hpp"

#include "Events/InputEvent.hpp"

Movement::Movement(World& world) : System<Controller, Velocity, Acceleration, EntityFlag, Transform, Collider>(world)
{

}

Movement::~Movement()
{
    
}

void Movement::Update(World& world, const unsigned long entityIndex)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
    Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);
    Acceleration* acceleration = static_cast<Acceleration*>(entity[Component<Acceleration>::Id]);
    Velocity* velocity = static_cast<Velocity*>(entity[Component<Velocity>::Id]);
    EntityFlag* entityFlag = static_cast<EntityFlag*>(entity[Component<EntityFlag>::Id]);

        
    if(!controller->GetMoveLeft() && !controller->GetMoveRight())
    {
        StopMove(world, entityIndex);
    }
            
    if(controller->GetMoveLeft())
    {
        acceleration->AccelerationX = -acceleration->AccelerationPerFrameX;
    }
    else if(controller->GetMoveRight())
    {
        acceleration->AccelerationX = acceleration->AccelerationPerFrameX;
    }

	if (controller->WantToJump())
	{
		Jump(world, entityIndex);
		controller->SetWantToJump(false);
	}
            
    if((entityFlag->GetEntityFlag() & GameObjectFlag::GRAVITY) == GameObjectFlag::GRAVITY)
    {
        acceleration->AccelerationY = Constants::IN_GAME_GRAVITY;
    }

    float speedX = velocity->SpeedX;
    float speedY = velocity->SpeedY;
    float maxSpeedX = velocity->MaxSpeedX;
    float maxSpeedY = velocity->MaxSpeedY;
            
    speedX += acceleration->AccelerationX * FPS::GetSpeedFactor();
    speedY += acceleration->AccelerationY * FPS::GetSpeedFactor();
            
    if(speedX > maxSpeedX) speedX = maxSpeedX;
    if(speedX < -maxSpeedX) speedX = -maxSpeedX;
    if(speedY > maxSpeedY) speedY = maxSpeedY;
    if(speedY < -maxSpeedY) speedY = -maxSpeedY;
            
    velocity->SpeedX = speedX;
    velocity->SpeedY = speedY;
            
    MoveTo(world, entityIndex, speedX, speedY);
}

void Movement::StopMove(World& world, const unsigned long entityIndex)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
    Acceleration* acceleration = static_cast<Acceleration*>(entity[Component<Acceleration>::Id]);
    Velocity* velocity = static_cast<Velocity*>(entity[Component<Velocity>::Id]);

    if(velocity->SpeedX > 0) acceleration->AccelerationX = -2 * acceleration->AccelerationPerFrameX;
    if(velocity->SpeedX < 0) acceleration->AccelerationX = 2 * acceleration->AccelerationPerFrameX;
    
    if(velocity->SpeedX < 2.0f && velocity->SpeedX > -2.0f) {
        acceleration->AccelerationX = 0;
        velocity->SpeedX = 0;
    }
}

void Movement::MoveTo(World& world, const unsigned long entityIndex, float x, float y)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
    Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);
    Velocity* velocity = static_cast<Velocity*>(entity[Component<Velocity>::Id]);
	EntityFlag* entityFlag = static_cast<EntityFlag*>(entity[Component<EntityFlag>::Id]);
	Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

    if(x == 0 && y == 0) return;
    
    double stepX = 0; // atomic step on x axis
    double stepY = 0; // atomic step on y axis
    
    x *= FPS::GetSpeedFactor();
    y *= FPS::GetSpeedFactor();
    
    if(x != 0)
    {
        if(x >= 0)
        {
            stepX = FPS::GetSpeedFactor();
        }
        else
        {
            stepX = -FPS::GetSpeedFactor();
        }
    }
    if(y != 0)
    {
        if(y >= 0)
        {
            stepY = FPS::GetSpeedFactor();
        }
        else
        {
            stepY = -FPS::GetSpeedFactor();
        }
    }
    
    while(true)
    {
        if((entityFlag->GetEntityFlag() & GameObjectFlag::GHOST) == GameObjectFlag::GHOST)
        {
            if(PosValid(world, entityIndex, transform->GetPosition().x + stepX, transform->GetPosition().y + stepY))
            {
				transform->SetPosition(sf::Vector2f(transform->GetPosition().x + stepX, transform->GetPosition().y + stepY));
            }
        }
        else
        {
            // movement on X axis
            if(PosValid(world, entityIndex, transform->GetPosition().x + stepX, transform->GetPosition().y))
            {
				transform->SetPosition(sf::Vector2f(transform->GetPosition().x + stepX, transform->GetPosition().y));
            }
            else
            {
                velocity->SpeedX = 0;
            }
            
            // movement on Y axis
            if(PosValid(world, entityIndex, transform->GetPosition().x, transform->GetPosition().y + stepY))
            {
				transform->SetPosition(sf::Vector2f(transform->GetPosition().x, transform->GetPosition().y + stepY));
            }
            else
            {
                velocity->SpeedY = 0;
            }
            //controller->SetCanJump(velocity->SpeedY == 0); //avoid double, triple, ... n jump. Jump allowed only when the ground is reached.
			controller->SetFreeFalling(velocity->SpeedY != 0); //this is used to stop the jumping animation or any other animation triggered from a free fall
        }
        
        x -= stepX;
        y -= stepY;
        
        if(stepX > 0 && x <= 0) stepX = 0; // if going to the right but reached/passed the x point
        if(stepX < 0 && x >= 0) stepX = 0; // if going to the left but reached/passed the x point
        if(stepY > 0 && y <= 0) stepY = 0; // same as above but for downward direction
        if(stepY < 0 && y >= 0) stepY = 0; // same as above but for upward direction
        if(x == 0) stepX = 0;
        if(y == 0) stepY = 0;
        if(x == 0 && y == 0) break;
        if(stepX == 0 && stepY == 0) break;
    }
    
}

bool Movement::PosValid(World& world, const unsigned long entityIndex, float x, float y)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
	Transform* transform = static_cast<Transform*>(entity[Transform::Id]);
	Collider* collider = static_cast<Collider*>(entity[Collider::Id]);

    sf::Vector2f m_originalPosition = transform->GetPosition();
	transform->SetPosition(sf::Vector2f(x, y));
    bool posValid = false;
    
    // the transform is always at the center of the collider
    const auto halfWidthCollider { collider->GetColliderRect().width / 2 };
    const auto halfHeightCollider { collider->GetColliderRect().height / 2 };

    bool insideXLimitMap = !(transform->GetPosition().x - halfWidthCollider < 0 ||
		transform->GetPosition().x + halfWidthCollider > Engine::GetInstance().GetMapLoader().getMapSize().x);
    bool insideYLimitMap = !(transform->GetPosition().y - halfHeightCollider < 0 ||
		transform->GetPosition().y + halfHeightCollider > Engine::GetInstance().GetMapLoader().getMapSize().y);
    
	//prevent player from falling from map's limits, thanks to the posValid initialized to false
    if(insideXLimitMap && insideYLimitMap)
    {
		posValid = CollisionDetectionUtils::PhysicsCollides(world, entityIndex) ? false : true;
    }
	transform->SetPosition(m_originalPosition);
    return posValid;
}

bool Movement::Jump(World& world, const unsigned long entityIndex)
{
	std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
	Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);
	Velocity* velocity = static_cast<Velocity*>(entity[Component<Velocity>::Id]);

	if (!controller->CanJump()) return false;

	controller->SetJumping(true);
	EventManager::QueueEvent(new InputEvent(InputEventType::JUMP_START, entityIndex));

	velocity->SpeedY = -velocity->MaxSpeedY;
	return true;
}

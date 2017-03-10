//
//  Movement.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Movement.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "Collider.hpp"
#include "FPS.hpp"
#include "CollisionDetectionUtils.hpp"

Movement::Movement(World& world) : System<Controller, Velocity, Acceleration, EntityFlag, Transform>(world)
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

        
    if(!controller->MoveLeft && !controller->MoveRight)
    {
        StopMove(world, entityIndex);
    }
            
    if(controller->MoveLeft)
    {
        acceleration->AccelerationX = -acceleration->AccelerationPerFrameX;
    }
    else if(controller->MoveRight)
    {
        acceleration->AccelerationX = acceleration->AccelerationPerFrameX;
    }
            
    if((entityFlag->GetEntityFlag() & GameObjectFlag::GRAVITY) == GameObjectFlag::GRAVITY)
    {
        acceleration->AccelerationY = Constants::IN_GAME_GRAVITY;
    }
            
//            float speedX = velocity.GetSpeedX();
//            float speedY = velocity.GetSpeedY();
//            float maxSpeedX = velocity.GetMaxSpeedX();
//            float maxSpeedY = velocity.GetMaxSpeedY();

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

    if(x > 2344){ //Debug TODO remove this!
        std::cout << "It's a big mess";
    }
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
            if(PosValid(world, entityIndex, transform->GetPosition(world, entityIndex).x + stepX, transform->GetPosition(world, entityIndex).y + stepY))
            {
				transform->SetPosition(world, entityIndex, sf::Vector2f(transform->GetPosition(world, entityIndex).x + stepX, transform->GetPosition(world, entityIndex).y + stepY));
            }
        }
        else
        {
            // movement on X axis
            if(PosValid(world, entityIndex, transform->GetPosition(world, entityIndex).x + stepX, transform->GetPosition(world, entityIndex).y))
            {
				transform->SetPosition(world, entityIndex, sf::Vector2f(transform->GetPosition(world, entityIndex).x + stepX, transform->GetPosition(world, entityIndex).y));
            }
            else
            {
                velocity->SpeedX = 0;
            }
            
            // movement on Y axis
            if(PosValid(world, entityIndex, transform->GetPosition(world, entityIndex).x, transform->GetPosition(world, entityIndex).y + stepY))
            {
				transform->SetPosition(world, entityIndex, sf::Vector2f(transform->GetPosition(world, entityIndex).x, transform->GetPosition(world, entityIndex).y + stepY));
            }
            else
            {
                velocity->SpeedY = 0;
            }
            controller->CanJump = velocity->SpeedY == 0;
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
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);
	Transform* transform = static_cast<Transform*>(entity[Transform::Id]);


    sf::Vector2f originalPosition = transform->GetPosition(world, entityIndex);
	transform->SetPosition(world, entityIndex, sf::Vector2f(x, y));
    bool posValid = false;
    
    bool insideXLimitMap = !(transform->GetPosition(world, entityIndex).x <= 0 ||
		transform->GetPosition(world, entityIndex).x + appearance->GetSprite()->getLocalBounds().width >= Engine::GetInstance().GetMapLoader().getMapSize().x);
    bool insideYLimitMap = !(transform->GetPosition(world, entityIndex).y <= 0 ||
		transform->GetPosition(world, entityIndex).y + appearance->GetSprite()->getLocalBounds().height >= Engine::GetInstance().GetMapLoader().getMapSize().y);
    //prevent player from falling from map's limits, thanks to the posValid initialized to false
    if( appearance->IsSpriteLoaded() && insideXLimitMap && insideYLimitMap)
    {
        if( (world.EntitiesComponentsMasks[entityIndex] & Component<Collider>::Id) == Component<Collider>::Id) //only entities will collider will check against collisions
        {
            posValid = CollisionDetectionUtils::Collides(world, entityIndex) ? false : true;
        }
        else posValid = true;
    }
	transform->SetPosition(world, entityIndex, originalPosition);
    return posValid;
}

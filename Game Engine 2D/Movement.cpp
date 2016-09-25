//
//  Movement.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Movement.hpp"
#include "Components.hpp"
#include "SystemManager.hpp"
#include "World.hpp"
#include "Engine.hpp"
#include "FPS.hpp"
#include "CollisionDetection.hpp"

Movement::Movement() : SystemBase()
{

}

Movement::~Movement()
{
    
}

void Movement::OnUpdate()
{
    World& world = Engine::GetInstance().World;
//    for(std::vector<int>::const_iterator entity = world.EntitiesMasks.begin(); entity != world.EntitiesMasks.end(); ++entity)
    for(int i = 0; i < world.EntitiesMasks.size(); ++i)
    {
        if((world.EntitiesMasks[i] & MOVEMENT_MASK) == (MOVEMENT_MASK))
        {
            //TODO I'd like to check if the Controller at that
            Controller& controller = *world.Controller[i];
            Acceleration& acceleration = *world.Acceleration[i];
            Velocity& velocity = *world.Velocity[i];
            EntityFlag& entityFlag = *world.EntityFlag[i];
            
        
        
            if(!controller.MoveLeft && !controller.MoveRight)
            {
                StopMove(world, i);
            }
            
            if(controller.MoveLeft)
            {
                acceleration.AccelerationX = -acceleration.AccelerationPerFrameX;
            }
            else if(controller.MoveRight)
            {
                acceleration.AccelerationX = acceleration.AccelerationPerFrameX;
            }
            
            if((entityFlag.GetEntityFlag() & GameObjectFlag::GRAVITY) == GameObjectFlag::GRAVITY)
            {
                acceleration.AccelerationY = Constants::IN_GAME_GRAVITY;
            }
            
//            float speedX = velocity.GetSpeedX();
//            float speedY = velocity.GetSpeedY();
//            float maxSpeedX = velocity.GetMaxSpeedX();
//            float maxSpeedY = velocity.GetMaxSpeedY();

            float speedX = velocity.SpeedX;
            float speedY = velocity.SpeedY;
            float maxSpeedX = velocity.MaxSpeedX;
            float maxSpeedY = velocity.MaxSpeedY;
            
            speedX += acceleration.AccelerationX * FPS::GetSpeedFactor();
            speedY += acceleration.AccelerationY * FPS::GetSpeedFactor();
            
            if(speedX > maxSpeedX) speedX = maxSpeedX;
            if(speedX < -maxSpeedX) speedX = -maxSpeedX;
            if(speedY > maxSpeedY) speedY = maxSpeedY;
            if(speedY < -maxSpeedY) speedY = -maxSpeedY;
            
            velocity.SpeedX = speedX;
            velocity.SpeedY = speedY;
            
            MoveTo(world, i, speedX, speedY);
        }
    }
}

//void Movement::MoveEntity(const World& world, const int entityIndex)
//{
////    World world = Engine::GetInstance()->world;
//    for(std::vector<int>::const_iterator entity = world.EntitiesMasks.begin(); entity != world.EntitiesMasks.end(); ++entity)
//    {
//        if(*entity & MOVEMENT_MASK == MOVEMENT_MASK)
//        {
////            world->
//        }
//    }
//}

void Movement::StopMove(const World& world, const unsigned long entityIndex)
{
//    World world = Engine::GetInstance()->world;
    Velocity& velocity = *world.Velocity[entityIndex];
    Acceleration& acceleration = *world.Acceleration[entityIndex];
    if(velocity.SpeedX > 0) acceleration.AccelerationX = -2 * acceleration.AccelerationPerFrameX;
    if(velocity.SpeedX < 0) acceleration.AccelerationX = 2 * acceleration.AccelerationPerFrameX;
    
    if(velocity.SpeedX < 2.0f && velocity.SpeedX > -2.0f) {
        acceleration.AccelerationX = 0;
        velocity.SpeedX = 0;
    }
}

void Movement::MoveTo(const World& world, const unsigned long entityIndex, float x, float y)
{
    EntityFlag& entityFlag = *world.EntityFlag[entityIndex];
    Position& position = *world.Position[entityIndex];
    Controller& controller = *world.Controller[entityIndex];
    Velocity& velocity = *world.Velocity[entityIndex];
    
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
        if((entityFlag.GetEntityFlag() & GameObjectFlag::GHOST) == GameObjectFlag::GHOST)
        {
            if(PosValid(world, entityIndex, position.GetPosition(world, entityIndex).x + stepX, position.GetPosition(world, entityIndex).y + stepY))
            {
                position.SetPosition(world, entityIndex, sf::Vector2f(position.GetPosition(world, entityIndex).x + stepX, position.GetPosition(world, entityIndex).y + stepY));
            }
        }
        else
        {
            // movement on X axis
            if(PosValid(world, entityIndex, position.GetPosition(world, entityIndex).x + stepX, position.GetPosition(world, entityIndex).y))
            {
                position.SetPosition(world, entityIndex, sf::Vector2f(position.GetPosition(world, entityIndex).x + stepX, position.GetPosition(world, entityIndex).y));
            }
            else
            {
                velocity.SpeedX = 0;
            }
            
            // movement on Y axis
            if(PosValid(world, entityIndex, position.GetPosition(world, entityIndex).x, position.GetPosition(world, entityIndex).y + stepY))
            {
                position.SetPosition(world, entityIndex, sf::Vector2f(position.GetPosition(world, entityIndex).x, position.GetPosition(world, entityIndex).y + stepY));
            }
            else
            {
                velocity.SpeedY = 0;
            }
            position.CanJump = velocity.SpeedY == 0;
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

bool Movement::PosValid(const World& world, const unsigned long entityIndex, float x, float y)
{
    EntityFlag& entityFlag = *world.EntityFlag[entityIndex];
    Position& position = *world.Position[entityIndex];
    Controller& controller = *world.Controller[entityIndex];
    Velocity& velocity = *world.Velocity[entityIndex];
    Appearance& appearance = *world.Appearance[entityIndex];
    
    sf::Vector2f originalPosition = position.GetPosition(world, entityIndex);
    position.SetPosition(world, entityIndex, sf::Vector2f(x, y));
    bool posValid = false;
    
    //prevent player from falling from map's limits
    if( appearance.IsSpriteLoaded() &&
       !(position.GetPosition(world, entityIndex).x <= 0 ||
         position.GetPosition(world, entityIndex).x + appearance.GetSprite()->getLocalBounds().width >= Engine::GetInstance().GetMapLoader().GetMapSize().x) )
    {
        posValid = CollisionDetection::Collides(world, entityIndex) ? false : true; //TODO add collision detection
    }
    position.SetPosition(world, entityIndex, originalPosition);
    return posValid;
}
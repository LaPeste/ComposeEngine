//
//  Velocity.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Components/Velocity.hpp"

Velocity::Velocity(World& world, const unsigned long int entityIndex) :
    SpeedX(0), SpeedY(0), MaxSpeedX(Constants::PLAYER_MAXSPEED_X), MaxSpeedY(Constants::PLAYER_MAXSPEED_Y),
	Component(world, entityIndex)
{
    
}

Velocity::~Velocity()
{
    
}

//float Velocity::GetSpeedX() const
//{
//    return speedX;
//}
//
//void Velocity::SetSpeedX(float speed)
//{
//    speedX = speed;
//}
//
//float Velocity::GetSpeedY() const
//{
//    return speedY;
//}
//
//void Velocity::SetSpeedY(float speed)
//{
//    speedY = speed;
//}
//
//float Velocity::GetMaxSpeedX() const
//{
//    return maxSpeedX;
//}
//
//void Velocity::SetMaxSpeedX(float speedX)
//{
//    maxSpeedX = speedX;
//}
//
//float Velocity::GetMaxSpeedY() const
//{
//    return maxSpeedY;
//}
//
//void Velocity::SetMaxSpeedY(float speedY)
//{
//    maxSpeedY = speedY;
//}

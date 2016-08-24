//
//  Acceleration.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Acceleration.hpp"

Acceleration::Acceleration(const float accelerationPerFrameX, const float accelerationPerFrameY) :
    AccelerationX(0), AccelerationY(0),
    AccelerationPerFrameX(accelerationPerFrameX), AccelerationPerFrameY(accelerationPerFrameY)
{
    
}
//
//float Acceleration::GetAccelerationX() const
//{
//    return accelerationX;
//}
//
//void Acceleration::SetAccelerationX(const float accelerationX)
//{
//    Acceleration::accelerationX = accelerationX;
//}
//
//float Acceleration::GetAccelerationY() const
//{
//    return accelerationY;
//}
//
//void Acceleration::SetAccelerationY(const float accelerationY)
//{
//    Acceleration::accelerationY = accelerationY;
//}
//
//float Acceleration::GetAccelerationPerFrameX() const
//{
//    return accelerationPerFrameX;
//}
//
//void Acceleration::SetAccelerationPerFrameX(const float accelerationX)
//{
//    Acceleration::accelerationPerFrameX = accelerationX;
//}
//
//float Acceleration::GetAccelerationPerFrameY() const
//{
//    return accelerationPerFrameY;
//}
//
//void Acceleration::SetAccelerationPerFrameY(const float accelerationY)
//{
//    Acceleration::accelerationPerFrameY = accelerationY;
//}
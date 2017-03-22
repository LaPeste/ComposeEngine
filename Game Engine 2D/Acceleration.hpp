//
//  Acceleration.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _ACCELERATION_HPP_
#define _ACCELERATION_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Acceleration : public Component<Acceleration>
{
public:
    Acceleration(World& world, const unsigned long int entityIndex, const float accelerationPerFrameX, const float accelerationPerFrameY);
	~Acceleration();
    
//    float GetAccelerationX() const;
//    void SetAccelerationX(const float accelerationX);
//    float GetAccelerationY() const;
//    void SetAccelerationY(const float accelerationY);
//    float GetAccelerationPerFrameX() const;
//    void SetAccelerationPerFrameX(const float accelerationX);
//    float GetAccelerationPerFrameY() const;
//    void SetAccelerationPerFrameY(const float accelerationY);
    
    
//private:
    float AccelerationX, AccelerationY;
    float AccelerationPerFrameX, AccelerationPerFrameY; //amount at which the acceleration can increase or decrease each frame
    
};

#endif /* _ACCELERATION_HPP_ */

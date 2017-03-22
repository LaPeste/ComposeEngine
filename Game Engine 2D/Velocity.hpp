//
//  Velocity.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _VELOCITY_HPP_
#define _VELOCITY_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Velocity : public Component<Velocity>
{
public:
    Velocity(World& world, const unsigned long int entityIndex);
    ~Velocity();
    
//    float GetSpeedX() const;
//    void SetSpeedX(float speedX);
//    float GetSpeedY() const;
//    void SetSpeedY(float speedY);
//    float GetMaxSpeedX() const;
//    void SetMaxSpeedX(float maxSpeedX);
//    float GetMaxSpeedY() const;
//    void SetMaxSpeedY(float maxSpeedY);
    
//private:
    float SpeedX;
    float SpeedY;
    float MaxSpeedX;
    float MaxSpeedY;
};

#endif /* _VELOCITY_HPP_ */

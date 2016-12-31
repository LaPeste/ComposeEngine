//
//  Controller.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Controller : public Component<Controller>
{
public:
    Controller();
    
    bool MoveRight;
    bool MoveLeft;
    bool Crouch;
    bool CanJump; //used to check conditions like: touching the ground etc etc
};

#endif /* _CONTROLLER_HPP_ */

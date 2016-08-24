//
//  Controller.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "stdafx.h"

class Controller
{
public:
    Controller();
    
    bool MoveLeft;
    bool MoveRight;
    bool Crouch;
    bool Jump();

private:
};

#endif /* _CONTROLLER_HPP_ */

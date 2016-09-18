//
//  SystemBase.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _SYSTEM_BASE_HPP_
#define _SYSTEM_BASE_HPP_

#include "stdafx.h"
#include "World.hpp"

class SystemBase
{
public:
    SystemBase();
    
    virtual void OnStart();
    virtual void OnInput(const sf::Event& event);
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnExit();
    
private:
    
};

#endif /* _SYSTEM_BASE_HPP_ */

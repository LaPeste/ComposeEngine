//
//  SystemBase.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/11/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _SYSTEM_BASE_HPP_
#define _SYSTEM_BASE_HPP_

#include "stdafx.h"

class SystemBase
{
public:
    SystemBase();
    
//    virtual SystemBase* GetSystem() const = 0;
    
    virtual void OnStart();
    virtual void OnInput(const sf::Event& event);
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnExit();

protected:
    static unsigned long int SystemCounter; //used for assigning a unique id to a system
};

#endif /* _SYSTEM_BASE_HPP_ */

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

/*!
 * Class needed in order to give a common base class to systems when called by SystemManager
 */

class SystemBase
{
public:
    SystemBase();
	virtual ~SystemBase();

    virtual void OnStart() = 0;
    virtual void OnInput(const sf::Event& event) = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
	virtual void OnLateUpdate() = 0;
	//virtual void OnCollision() = 0;
    virtual void OnExit() = 0;

protected:
    static unsigned long int SystemCounter; //used for assigning a unique id to a system
};

#endif /* _SYSTEM_BASE_HPP_ */

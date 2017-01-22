//
//  System.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include "stdafx.h"
#include "World.hpp"
#include "SystemBase.hpp"

//systems
#include "Appearance.hpp"
#include "Animation.hpp"
#include "Appearance.hpp"
#include "EntityFlag.hpp"
#include "Acceleration.hpp"
#include "Velocity.hpp"
#include "Controller.hpp"

template<typename First, typename ...Rest> //variadic template
class System : public SystemBase
{
public:
    
    System(World& world);
    
//    static System* const Create();
    
    const unsigned long int GetComponentBitMask() const;

	static unsigned long int Id;
    
private:
    unsigned long int componentsBitMask;
    
    template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
    void CalculateComponentsBitMask();
    
    template <typename LastInternal>
    void CalculateComponentsBitMask();
    
    
};

#include "System.tpp"

#endif /* _SYSTEM_HPP_ */

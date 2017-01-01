 //
//  System.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "System.hpp"
#include "Component.hpp"

template<typename First, typename ...Rest>
unsigned long int System<First,Rest...>::Id(0);

template<typename First, typename ...Rest>
System<First,Rest...>::System(World& world) : componentsBitMask(0)
{
    if(Id == 0)
    {
        Id = 1 << SystemCounter++;
    }
    
    CalculateComponentsBitMask<First, Rest...>();
}

//template<typename First, typename ...Rest>
//System* const System::Create()
//{
//    System* system = new System();
//    CalculateComponentsBitMask<First,Rest...>();
//    return system;
//}

template<typename First, typename ...Rest>
template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
void System<First,Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<FirstInternal>::Id;
    CalculateComponentsBitMask<SecondInternal, RestInternal...>();
}



template<typename First, typename ...Rest>
template<typename LastInternal>
void System<First,Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<LastInternal>::Id;
}


template<typename First, typename ...Rest>
const unsigned long int System<First,Rest...>::GetComponentBitMask() const
{
    return componentsBitMask;
}

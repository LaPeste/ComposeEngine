//
//  System.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "System.hpp"
#include "Component.hpp"

template<typename First, typename Second, typename ...Rest>
unsigned long int System<First, Second, Rest...>::Id(0);

template<typename First, typename Second, typename ...Rest>
System<First, Second, Rest...>::System(World& world) : componentsBitMask(0)
{
    if(Id == 0)
    {
        Id = 1 << SystemCounter++;
    }
    
    CalculateComponentsBitMask<First, Second, Rest...>();
}

//template<typename First, typename Second, typename ...Rest>
//System* const System::Create()
//{
//    System* system = new System();
//    CalculateComponentsBitMask<First, Second, Rest...>();
//    return system;
//}

template<typename First, typename Second, typename ...Rest>
template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
void System<First, Second, Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<FirstInternal>().Id;
    CalculateComponentsBitMask<SecondInternal, RestInternal...>();
}

template<typename First, typename Second, typename ...Rest>
template<typename LastInternal>
void System<First, Second, Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<LastInternal>().Id;
}


template<typename First, typename Second, typename ...Rest>
const unsigned long int System<First, Second, Rest...>::GetComponentBitMask() const
{
    return componentsBitMask;
}

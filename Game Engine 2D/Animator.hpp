//
//  Animator.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _ANIMATOR_HPP_
#define _ANIMATOR_HPP_

#include "stdafx.h"
#include "System.hpp"

#define ANIMATION_MASK Components::APPEARANCE | Components::ANIMATION | Components::CONTROLLER

//This class assumes that the sprite set is horizontally developed

template<typename First, typename ...Rest>
class Animator : public System<First,Rest...>
{
public:
    Animator(World& world);
    ~Animator();
    
    void OnUpdate() override;
    
private:
    void Animate(const World& world, const unsigned long entityIndex);
};

#include "Animator.tpp"

#endif /* _ANIMATOR_HPP_ */

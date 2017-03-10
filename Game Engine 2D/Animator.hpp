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

class Animator : public System<Appearance, Animation, Controller>
{
public:
    Animator(World& world);
    ~Animator();
        
private:
    void Animate(World& world, const unsigned long entityIndex);

	void Update(World& world, const unsigned long entityIndex) override;
};

#endif /* _ANIMATOR_HPP_ */

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
#include "Systems/System.hpp"

class Animator : public System<Appearance, Animation, Controller>
{
public:
    Animator(World& world);
    ~Animator() override;
	
private:
    void Animate(World& world, const unsigned long entityIndex);

	void Update(World& world, const unsigned long entityIndex) override;
};

#endif /* _ANIMATOR_HPP_ */

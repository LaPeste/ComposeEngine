//
//  Controller.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "stdafx.h"
#include "System.hpp"
#include "Event.hpp"

class InputSystem : public System<Controller, Velocity>, public Event
{
public:
    InputSystem(World& world);
    ~InputSystem();
        
    void OnKeyUp(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex) override;
    void OnKeyDown(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex) override;

private:
	void Input(World& world, const unsigned long entityIndex, const sf::Event& event) override;
};

#endif /* _INPUT_HPP_ */

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

#define INPUT_MASK Components::POSITION, Components::VELOCITY, Components::ACCELERATION, Components::CONTROLLER

template<typename First, typename Second, typename ...Rest>
class Input : public System<First, Second, Rest...>, public Event
{
public:
    Input(World& world);
    ~Input();
    
    void OnInput(const sf::Event& event) override;
    
    void OnKeyUp(const sf::Event::KeyEvent& input, const World& world, const unsigned long entityIndex) override;
    void OnKeyDown(const sf::Event::KeyEvent& input, const World& world, const unsigned long entityIndex) override;

private:
    bool Jump(const World& world, const unsigned long entityIndex);
};

#include "Input.tpp"

#endif /* _INPUT_HPP_ */

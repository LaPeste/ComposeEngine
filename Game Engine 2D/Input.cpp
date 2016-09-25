//
//  Controller.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Controller.hpp"
#include "Engine.hpp"
#include "Input.hpp"

Input::Input()
{
    
}

void Input::OnInput(const sf::Event &event)
{
    World& world = Engine::GetInstance().World;
    //    for(std::vector<int>::const_iterator entity = world.EntitiesMasks.begin(); entity != world.EntitiesMasks.end(); ++entity)
    for(int i = 0; i < world.EntitiesMasks.size(); ++i)
    {
        if((world.EntitiesMasks[i] & INPUT_MASK) == (INPUT_MASK))
        {
            OnEvent(event, world, i);
        }
    }
}

void Input::OnKeyUp(const sf::Event::KeyEvent& input, const World& world, const unsigned long entityIndex)
{
    Controller& controller = *world.Controller[entityIndex];
    
    switch (input.code)
    {
        case sf::Keyboard::Key::A:
            controller.MoveLeft = false;
            break;
        case sf::Keyboard::Key::D:
            controller.MoveRight = false;
            break;
        case sf::Keyboard::Key::S:
            controller.Crouch = false;
            break;
        case sf::Keyboard::Key::Space:
            
            break;
            //Add the cases that you need
        default:
            break;
    }
}

void Input::OnKeyDown(const sf::Event::KeyEvent& input, const World& world, const unsigned long entityIndex)
{
    Controller& controller = *world.Controller[entityIndex];
    
    switch (input.code)
    {
        case sf::Keyboard::Key::A:
            controller.MoveLeft = true;
            break;
        case sf::Keyboard::Key::D:
            controller.MoveRight = true;
            break;
        case sf::Keyboard::Key::S:
            controller.Crouch = true;
            break;
        case sf::Keyboard::Key::Space:
            Jump(world, entityIndex);
            break;
            //Add the cases that you need
        default:
            break;
    }
}

bool Input::Jump(const World& world, const unsigned long entityIndex)
{
    Position& position = *world.Position[entityIndex];
    Velocity& velocity = *world.Velocity[entityIndex];
    if(!position.CanJump) return false;
    
    velocity.SpeedY = -velocity.MaxSpeedY;
    return true;
}
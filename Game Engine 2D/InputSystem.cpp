//
//  Controller.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Controller.hpp"
#include "Engine.hpp"
#include "InputSystem.hpp"

InputSystem::InputSystem(World& world) : System<Controller, Velocity, Acceleration, Appearance>(world)
{
    
}

InputSystem::~InputSystem(){}

void InputSystem::Input(World& world, const unsigned long entityIndex, const sf::Event& event)
{
	OnEvent(event, world, entityIndex);
}

void InputSystem::OnKeyUp(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex)
{
    std::map<unsigned long int, ComponentBase*> entity = world.EntitiesComponentsMatrix[entityIndex];
    Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);

    switch (input.code)
    {
        case sf::Keyboard::Key::A:
            controller->MoveLeft = false;
            break;
        case sf::Keyboard::Key::D:
            controller->MoveRight = false;
            break;
        case sf::Keyboard::Key::S:
            controller->Crouch = false;
            break;
        case sf::Keyboard::Key::Space:
            
            break;
            //Add the cases that you need
        default:
            break;
    }
}

void InputSystem::OnKeyDown(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex)
{
    std::map<unsigned long int, ComponentBase*> entity = world.EntitiesComponentsMatrix[entityIndex];
    std::cout << "id of controller= " << Component<Controller>::Id << std::endl;
    Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);

    switch (input.code)
    {
        case sf::Keyboard::Key::A:
            controller->MoveLeft = true;
            break;
        case sf::Keyboard::Key::D:
            controller->MoveRight = true;
            break;
        case sf::Keyboard::Key::S:
            controller->Crouch = true;
            break;
        case sf::Keyboard::Key::Space:
            Jump(world, entityIndex);
            break;
            //Add the cases that you need
        default:
            break;
    }
}

bool InputSystem::Jump(World& world, const unsigned long entityIndex)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
    Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);
    Velocity* velocity = static_cast<Velocity*>(entity[Component<Velocity>::Id]);

    if(!controller->CanJump) return false;
    
    velocity->SpeedY = -velocity->MaxSpeedY;
    return true;
}

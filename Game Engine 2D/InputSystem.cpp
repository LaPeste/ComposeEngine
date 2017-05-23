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

//DEBUG to remove
#include "Transform.hpp"


InputSystem::InputSystem(World& world) : System<Controller, Velocity>(world)
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
            controller->SetMoveLeft(false);
            break;
        case sf::Keyboard::Key::D:
			controller->SetMoveRight(false);
            break;
        case sf::Keyboard::Key::S:
            controller->SetCrouch(false);
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
	Controller* controller = static_cast<Controller*>(entity[Component<Controller>::Id]);

	//DEBUG to put mario where it was
	Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

    switch (input.code)
    {
        case sf::Keyboard::Key::A:
			controller->SetMoveRight(false); //to simulate that only one direction button is pressed at a time
            controller->SetMoveLeft(true);
            break;
        case sf::Keyboard::Key::D:
			controller->SetMoveLeft(false); //to simulate that only one direction button is pressed at a time
            controller->SetMoveRight(true);
            break;
        case sf::Keyboard::Key::S:
            controller->SetCrouch(true);
            break;
		case sf::Keyboard::Key::R:
			//DEBUG to unstick mario where it was
			transform->SetPosition(sf::Vector2f(1088, 321));
			break;
        case sf::Keyboard::Key::Space:
            controller->SetWantToJump(true);
            break;
            //Add the cases that you need
        default:
            break;
    }
}
//
//  System.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include "stdafx.h"
#include "World.hpp"
#include "SystemBase.hpp"

//systems
#include "Appearance.hpp"
#include "Animation.hpp"
#include "Appearance.hpp"
#include "EntityFlag.hpp"
#include "Acceleration.hpp"
#include "Velocity.hpp"
#include "Controller.hpp"
#include "Collider.hpp"
#include "FieldOfView.hpp"

/*!
 * In the template it's expected to go all needed Components for the current System to work properly.
 */

template<typename First, typename ...Rest> //variadic template
class System : public SystemBase
{
public:
    
    System(World& world);
	~System() override;

    const unsigned long int GetComponentBitMask() const;

	static unsigned long int Id;

	void OnStart() override;
	void OnInput(const sf::Event& event) override;
	void OnUpdate() override;
	void OnLateUpdate() override;
	//void OnCollision() override;
	void OnRender() override;
	void OnExit() override;

	//TODO get the right name of systems https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/10066918/
	//virtual const std::string& GetSystemName() const; //implement if you want a more accurate debug logging

protected:
	World& world;

    
private:
    unsigned long int componentsBitMask;
    
    template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
    void CalculateComponentsBitMask();
    
    template <typename LastInternal>
    void CalculateComponentsBitMask();

	//The methods below are virtual and not abstract otherwise I am forced to define a body for each function in every subclass even if I don't need that specific function.
	//The problem is that if a subclass doesn't override an abstract method of a superclass then it can't be instantiated because it remains an abstract class.
	//Making them virtual allows a subclass not to be forced to define methods not needed and still not being abstract, hence instantiable.
	virtual void Start(World& world, const unsigned long int entityIndex);
	virtual void Input(World& world, const unsigned long int entityIndex, const sf::Event& event);
	virtual void Update(World& world, const unsigned long int entityIndex);
	virtual void LateUpdate(World& world, const unsigned long int entityIndex);
	//virtual void Collision(World& world, const unsigned long int entityIndexA, const unsigned long int entityIndexB);
	virtual void Render(World& world, const unsigned long int entityIndex);
	virtual void Exit(World& world, const unsigned long int entityIndex);
};

#include "System.tpp"

#endif /* _SYSTEM_HPP_ */

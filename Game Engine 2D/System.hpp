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

template<typename First, typename ...Rest> //variadic template
class System : public SystemBase
{
public:
    
    System(World& world);
    
//    static System* const Create();
    
    const unsigned long int GetComponentBitMask() const;

	static unsigned long int Id;

	void OnStart() override;
	void OnInput(const sf::Event& event) override;
	void OnUpdate() override;
	void OnLateUpdate() override;
	void OnRender() override;
	void OnExit() override;

protected:
	World& world;

    
private:
    unsigned long int componentsBitMask;
    
    template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
    void CalculateComponentsBitMask();
    
    template <typename LastInternal>
    void CalculateComponentsBitMask();


	virtual void Start(World& world, const unsigned long int entityIndex);
	virtual void Input(World& world, const unsigned long int entityIndex, const sf::Event& event);
	virtual void Update(World& world, const unsigned long int entityIndex);
	virtual void LateUpdate(World& world, const unsigned long int entityIndex);
	virtual void Render(World& world, const unsigned long int entityIndex);
	virtual void Exit(World& world, const unsigned long int entityIndex);

	void SetIfUpdateMapObject(World& world, const unsigned long int entityIndex);
    
};

#include "System.tpp"

#endif /* _SYSTEM_HPP_ */

 //
//  System.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "System.hpp"
#include "Component.hpp"
#include "MapObjectComponent.hpp"

template<typename First, typename ...Rest>
unsigned long int System<First, Rest...>::Id(0);

template<typename First, typename ...Rest>
System<First,Rest...>::System(World& world) : componentsBitMask(0), System::world(world)
{
    if(Id == 0)
    {
        Id = 1 << SystemCounter++;
    }
    
    CalculateComponentsBitMask<First, Rest...>();
}

//template<typename First, typename ...Rest>
//System* const System::Create()
//{
//    System* system = new System();
//    CalculateComponentsBitMask<First,Rest...>();
//    return system;
//}

template<typename First, typename ...Rest>
template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
void System<First,Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<FirstInternal>::Id;
    CalculateComponentsBitMask<SecondInternal, RestInternal...>();
}



template<typename First, typename ...Rest>
template<typename LastInternal>
void System<First,Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<LastInternal>::Id;
}


template<typename First, typename ...Rest>
const unsigned long int System<First,Rest...>::GetComponentBitMask() const
{
    return componentsBitMask;
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnStart()
{
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if ((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
		{
			Start(world, i);
		}
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnInput(const sf::Event& event)
{
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if ((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
		{
			Input(world, i, event);
		}
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnUpdate()
{
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if ((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
		{
			Update(world, i);
		}
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnRender()
{
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if ((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
		{
			Render(world, i);
		}
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnLateUpdate()
{
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if ((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
		{
			LateUpdate(world, i);
		}
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnExit()
{
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if ((world.EntitiesComponentsMasks[i] & this->GetComponentBitMask()) == this->GetComponentBitMask())
		{
			Exit(world, i);
		}
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::Start(World& world, const unsigned long int entityIndex)
{

}

template<typename First, typename ...Rest>
void System<First, Rest...>::Input(World& world, const unsigned long int entityIndex, const sf::Event& event)
{

}

template<typename First, typename ...Rest>
void System<First, Rest...>::Update(World& world, const unsigned long int entityIndex)
{

}

template<typename First, typename ...Rest>
void System<First, Rest...>::LateUpdate(World& world, const unsigned long int entityIndex)
{

}

template<typename First, typename ...Rest>
void System<First, Rest...>::Render(World& world, const unsigned long int entityIndex)
{

}

template<typename First, typename ...Rest>
void System<First, Rest...>::Exit(World& world, const unsigned long int entityIndex)
{

}

template<typename First, typename ...Rest>
void System<First, Rest...>::SetIfUpdateMapObject(World& world, const unsigned long int entityIndex)
{
	if (world.EntitiesComponentsMatrix[entityIndex][MapObjectComponent::Id] != nullptr) //if it's a MapObject
	{
		world.EntitiesComponentsMatrix[entityIndex][MapObjectComponent::Id].SetToUpdate(true);
	}
}
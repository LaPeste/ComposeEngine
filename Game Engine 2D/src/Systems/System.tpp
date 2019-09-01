 //
//  System.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Systems/System.hpp"
#include "Entities/EntityManager.hpp"
#include "Events/EventListener.hpp"
#include "Events/AddedComponentEvent.hpp"

template<typename First, typename ...Rest>
unsigned long int System<First, Rest...>::Id(0);

template<typename First, typename ...Rest>
System<First,Rest...>::System(World& world) : componentsBitMask(0), currentWorld(world)
{
    if(Id == 0)
    {
        Id = 1 << SystemCounter++;
    }
    
    CalculateComponentsBitMask<First, Rest...>();

	std::function<void(Event<AddedComponentEvent>*)> method(
		[&](Event<AddedComponentEvent>* event)
	{
		auto* castedEvent = static_cast<AddedComponentEvent*>(event);
		const auto& gameObjectModified = castedEvent->GetGameObjectTarget();
		uint32_t entityId = gameObjectModified.GetEntityIndex();
		auto& world = gameObjectModified.GetWorld();
		if (Entity::HasComponent(world, entityId, GetComponentBitMask()))
		{
			auto searchedObj = m_cachedGameObjectTargets.find(&gameObjectModified);
			if (searchedObj == m_cachedGameObjectTargets.end())
			{
				m_cachedGameObjectTargets.insert(&gameObjectModified);
			}
		}
	});

	OnGameEvent<AddedComponentEvent>(method);
}

template<typename First, typename ...Rest>
System<First, Rest...>::~System() {}

template<typename First, typename ...Rest>
template<typename FirstInternal, typename SecondInternal, typename ...RestInternal>
void System<First,Rest...>::CalculateComponentsBitMask()
{
    componentsBitMask |= Component<FirstInternal>::Id;
	//Type... = pack expansion, which is: the name of the parameter pack is replaced by each of the elements from the pack, in order
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
	/*for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if (Entity::HasComponent(world, i, this->GetComponentBitMask()))
		{
			Start(world, i);
		}
	}*/
	for (auto* entity : m_cachedGameObjectTargets)
	{
		Start(currentWorld, entity->GetEntityIndex());
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnInput(const sf::Event& event)
{
	/*for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if (Entity::HasComponent(world, i, this->GetComponentBitMask()))
		{
			Input(world, i, event);
		}
	}*/

	//only the player is subjected to input
	if (Entity::HasComponent(currentWorld, EntityManager::GetPlayerId(), this->GetComponentBitMask()))
	{
		Input(currentWorld, EntityManager::GetPlayerId(), event);
	}

	/*for (auto* entity : m_cachedGameObjectTargets)
	{
		Input(world, entity->GetEntityIndex(), event);
	}*/
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnUpdate()
{
	/*for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if (Entity::HasComponent(world, i, this->GetComponentBitMask()))
		{
			Update(world, i);
		}
	}*/
	for (auto* entity : m_cachedGameObjectTargets)
	{
		Update(currentWorld, entity->GetEntityIndex());
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnRender()
{
	/*for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if (Entity::HasComponent(world, i, this->GetComponentBitMask()))
		{
			Render(world, i);
		}
	}*/
	for (auto* entity : m_cachedGameObjectTargets)
	{
		Render(currentWorld, entity->GetEntityIndex());
	}
}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnLateUpdate()
{
	/*for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if (Entity::HasComponent(world, i, this->GetComponentBitMask()))
		{
			LateUpdate(world, i);
		}
	}*/
	for (auto* entity : m_cachedGameObjectTargets)
	{
		LateUpdate(currentWorld, entity->GetEntityIndex());
	}
}

//template<typename First, typename ...Rest>
//void System<First, Rest...>::OnCollision()
//{
//	for (const auto& collision : world.GetCollisionEvents())
//	{
//		if (Entity::HasComponent(world, collision.GetEntityA(), this->GetComponentBitMask()) || 
//			Entity::HasComponent(world, collision.GetEntityB(), this->GetComponentBitMask()))
//		{
//			Collision(world, collision.GetEntityA(), collision.GetEntityB());
//		}
//	}
//}

template<typename First, typename ...Rest>
void System<First, Rest...>::OnExit()
{
	/*for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		if (Entity::HasComponent(world, i, this->GetComponentBitMask()))
		{
			Exit(world, i);
		}
	}*/
	for (auto* entity : m_cachedGameObjectTargets)
	{
		Exit(currentWorld, entity->GetEntityIndex());
	}
}

//template<typename First, typename ...Rest>
//const std::string & System<First, Rest...>::GetSystemName() const
//{
//	return typeid(*this).name();
//}

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

//template<typename First, typename ...Rest>
//void System<First, Rest...>::Collision(World& world, const unsigned long int entityIndexA, const unsigned long int entityIndexB)
//{}


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
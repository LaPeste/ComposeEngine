//
//  World.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _WORLD_HPP_
#define _WORLD_HPP_

#include "stdafx.h"
#include <functional>

#include "Components/ComponentBase.hpp"
#include "Systems/SystemBase.hpp"
#include "Components/Component.hpp"

class GameObject;

//Data holder for entities, components and systems. It can be seen as a level data holder.
using ComponentsMap = std::map<unsigned long int, ComponentBase*>;

class World
{
public:
    World();
    ~World();

	World(const World&) = delete; // C++11 feature
	World& operator=(const World&) = delete;
    
//private: TODO maybe make them private and use properties?

	//! To quickly query what components an entity at a certain index has.
    std::vector<unsigned long int> EntitiesComponentsMasks;

	//! It holds components per each entity. Each component can be quickly obtained by its id from the map of each entity.
    std::vector<ComponentsMap> EntitiesComponentsMatrix;

	//! All available systems in this world
    std::map<unsigned long int, SystemBase*> Systems;

	//! Connection between an entityIndex and the gameobject abstraction connected to it.
	std::map<unsigned long int, GameObject*> EntitiesHandles;

	// Methods

	template<typename T>
	T* GetComponent(unsigned long int entityIndex);

private:
};


template<typename T>
T* World::GetComponent(unsigned long int entityIndex)
{
	if (EntitiesHandles.find(entityIndex) == EntitiesHandles.end())
	{
		DEBUG_ERROR("Something went very wrong. There was no index " + std::to_string(entityIndex) + " in this world");
		return nullptr;
	}
	auto componentId = Component<T>::Id;
	if (!EntitiesComponentsMasks[entityIndex] & componentId)
	{
		DEBUG_WARNING("No component " + std::string(typeid(T).name()) + " was found.");
		return nullptr;
	}

	return static_cast<T*>(EntitiesComponentsMatrix[entityIndex][componentId]);
}

#endif /* _WORLD_HPP_ */

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

#include "ComponentBase.hpp"
#include "SystemBase.hpp"
#include "CollisionEvent.hpp"
#include "GameObject.hpp"

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
    std::vector<unsigned long int> EntitiesComponentsMasks; //defines components held by each entity
    std::vector<ComponentsMap> EntitiesComponentsMatrix;
    std::map<unsigned long int, SystemBase*> Systems;
	std::map<unsigned long int, GameObject*> EntitiesHandles;

	// Methods
	const std::vector<CollisionEvent>& GetCollisionEvents() const;
	void AddCollisionEvent(const CollisionEvent& event);
	void DeleteAllCollisionEvents();

private:
	std::vector<CollisionEvent> collisionEvents;
};



#endif /* _WORLD_HPP_ */

//
//  World.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "World.hpp"
#include "EventManager.hpp"

World::World() :
	EntitiesComponentsMasks(),
	EntitiesComponentsMatrix(),
	Systems(),
	EntitiesHandles()
{

}

World::~World()
{
    for(const auto& system : Systems)
    {
        delete system.second;
    }

	for (const auto& pair : EntitiesHandles)
	{
		delete(pair.second);
	}
	EntitiesHandles.clear();

    for(std::map<unsigned long int, ComponentBase*>& componentMap : EntitiesComponentsMatrix)
    {
        auto it = componentMap.begin();
		while(it != componentMap.end())
        {
			if (it->second != nullptr)
			{
				delete it->second;
				it = componentMap.erase(it); //returning the iterator from the erase allows not to have it invalidate but pointing to the next elem
			}
			else ++it;
        }
    }
}

const std::vector<CollisionEvent>& World::GetCollisionEvents() const
{
	return collisionEvents;
}

void World::AddCollisionEvent(const CollisionEvent& event)
{
	collisionEvents.push_back(event);
}

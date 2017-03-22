//
//  World.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "World.hpp"

World::World()
{

}

World::~World()
{
    for(const auto& system : Systems)
    {
        delete system.second;
    }


	//TODO I don't know why this corrupts the heap https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/9797950/
   // for(std::map<unsigned long int, ComponentBase*>& componentMap : EntitiesComponentsMatrix)
   // {
   //     for (auto it = componentMap.begin(); it != componentMap.end(); ++it)
   //     {
			//if (it->second != nullptr)
			//{
			//	delete it->second;
			//	it = componentMap.erase(it); //returning the iterator from the erase allows not to have it invalidate but pointing to the next elem
			//}
   //     }
   // }
}

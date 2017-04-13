//
//  EntityManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "EntityManager.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"

//TODO this has to go away as soon as an standard way of creating gameobjects is done
//#include "Collider.hpp"
//#include "Acceleration.hpp"
//#include "Controller.hpp"
//#include "Velocity.hpp"
#include "Transform.hpp"
#include "EntityFlag.hpp"

#include "Luigi.hpp"
#include "Door.hpp"

unsigned long int EntityManager::playerId(99999); //defaulted to a very big number
std::vector<CollisionEvent> EntityManager::collisionEvents;

void EntityManager::Init(World& world)
{
	Instantiate<Player>(world);
	Instantiate<Luigi>(world);

	world.EntitiesRegistry.insert(std::make_pair("Door", std::bind(&Instantiate<Door>, std::ref(world)))); //std::ref is crucial since without we're passing a copy of world, which will be destroyed (with destructor) right after the std::bind ends. For better info check this out  http://stackoverflow.com/questions/19859288/why-will-stdfunction-call-destructor-when-an-object-was-bound-to-a-member-func
	
    //populates the list of objects with objects coming from the map (tmx file)
	Engine& engine = Engine::GetInstance();
    std::vector<tmx::MapLayer>& layers = engine.GetMapLoader().getLayers();
	//for (std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
	for(int layerIndex = 0; layerIndex < layers.size(); ++layerIndex)
    {
		tmx::MapLayer& layer = layers[layerIndex];
        if(layer.name == Constants::COLLISION_LAYER)
        {
			std::vector<tmx::MapObject>::iterator objectIter = layer.objects.begin();
            while(objectIter != layer.objects.end())
            {
				std::string objName = objectIter->getName();
				if (world.EntitiesRegistry.find(objName) != world.EntitiesRegistry.end())
				{
					GameObject* gameObject = world.EntitiesRegistry[objName](world);
					objectIter->setVisible(false); //for now invisible, if possible, completely deleted
					Transform* transform = static_cast<Transform*>(world.EntitiesComponentsMatrix[gameObject->GetEntityIndex()][Transform::Id]);
					transform->SetPosition(objectIter->getPosition());
					objectIter = layer.objects.erase(objectIter);
				}
				else
				{
					++objectIter;
				}
            }
			//very confused why this doesn't do what I was expecting https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/10074378/
			engine.GetMapLoader().drawLayer(*engine.GetWindow(), layerIndex); //I was hoping for a redraw of the layer without the objects removed during the layer parsing... but it isn't so
        }
    }
}

const unsigned long EntityManager::CreateEntity(World& world, const GameObjectFlag& flags)
{
    for(int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
    {
        if(world.EntitiesComponentsMasks[i] == UtilConstants::NO_COMPONENTS) //then a corrispondent position in the components array already exist
        {
            FreeWorldFields(world, i);
            return i;
        }
    }
    
    world.EntitiesComponentsMasks.push_back(UtilConstants::NO_COMPONENTS);
    world.EntitiesComponentsMatrix.push_back(std::map<unsigned long int, ComponentBase*>());

	unsigned long int indexNewEntity = world.EntitiesComponentsMasks.size() - 1;
	AddComponent(world, indexNewEntity, new EntityFlag(world, indexNewEntity, flags));
    
    return indexNewEntity; //return size because you want to return an index that points to a newest entity
}

void EntityManager::DestroyEntity(World& world, const unsigned long index)
{
//    *world.EntitiesComponentsMasks[index] = Components::NONE;
    world.EntitiesComponentsMasks[index] = UtilConstants::NO_COMPONENTS;
}

const unsigned long EntityManager::GetPlayerId()
{
    return playerId;
}

void EntityManager::SetPlayerId(const unsigned long index)
{
    playerId = index;
}

void EntityManager::FreeWorldFields(World& world, const int index)
{
    world.EntitiesComponentsMasks[index] = UtilConstants::NO_COMPONENTS;
}

const std::vector<CollisionEvent>& EntityManager::GetCollisionEvents()
{
    return collisionEvents;
}

void EntityManager::AddCollisionEvent(const CollisionEvent& event)
{
    collisionEvents.push_back(event);
}

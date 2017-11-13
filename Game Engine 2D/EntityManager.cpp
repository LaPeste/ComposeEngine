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
	
    //populates the list of objects with objects coming from the map (tmx file)
	Engine& engine = Engine::GetInstance();
    std::vector<tmx::MapLayer>& layers = engine.GetMapLoader().getLayers();
	for(int layerIndex = 0; layerIndex < layers.size(); ++layerIndex)
    {
		tmx::MapLayer& layer = layers[layerIndex];
        if(layer.name == Constants::COLLISION_LAYER)
        {
			std::vector<tmx::MapObject>::iterator objectIter = layer.objects.begin();
			//check every object name in the layers, if exists in registry instantiate an object of that class
            while(objectIter != layer.objects.end())
            {
				std::string objName = objectIter->getName();
				if (Registry::GetGameObjectsRegistry().find(objName) != Registry::GetGameObjectsRegistry().end())
				{
					GameObject* gameObject = Registry::GetGameObjectsRegistry()[objName](world);
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
			engine.GetMapLoader().drawLayer(*engine.GetWindow(), layerIndex); //I was hoping for a redraw of the layer without the objects that were removed during the layer parsing... but it isn't so
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

void EntityManager::DestroyGameObject(GameObject* gameObject)
{
	unsigned long int index = gameObject->GetEntityIndex();
	World& world = gameObject->GetWorld();
	DeleteAllComponentsForEntity(world, index);
	DeleteEntityHandle(world, index);
    world.EntitiesComponentsMasks[index] = UtilConstants::NO_COMPONENTS;
	delete(gameObject);
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

void EntityManager::DeleteAllComponentsForEntity(World& world, unsigned long int entityIndex)
{
	std::map<unsigned long int, ComponentBase*>& entityMap = world.EntitiesComponentsMatrix[entityIndex];
	auto& iterComp = entityMap.begin();
	while (iterComp != entityMap.end())
	{
		delete(iterComp->second);
		++iterComp;
	}
	entityMap.clear();
}

void EntityManager::DeleteEntityHandle(World& world, unsigned long int entityIndex)
{
	if (world.EntitiesHandles.find(entityIndex) == world.EntitiesHandles.end())
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "you're trying to delete a handle that doesn't exist, since entityIndex=" << entityIndex << " could not be found!";
		Utils::PrintDebugLog(methodName, oss.str());

		throw 1;
	}

	world.EntitiesHandles.erase(entityIndex);
}

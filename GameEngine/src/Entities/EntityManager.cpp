//
//  EntityManager.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 20/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Entities/EntityManager.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"

//TODO this has to go away as soon as an standard way of creating gameobjects is done
//#include "Components/Collider.hpp"
//#include "Components/Acceleration.hpp"
//#include "Components/Controller.hpp"
//#include "Components/Velocity.hpp"
#include "Components/Transform.hpp"
#include "Components/EntityFlag.hpp"

#include "GameExample/GameObjects/Luigi.hpp"
#include "GameExample/GameObjects/Door.hpp"
#include "GameObjects/Player.hpp"

unsigned long int EntityManager::playerId(99999); //defaulted to a very big number

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
			// TODO put in rendering part of the engine
			//engine.GetMapLoader().drawLayer(*engine.GetWindow(), layerIndex);
        }
    }
}

const unsigned long EntityManager::CreateEntity(World& world, const GameObjectFlag& flags)
{
	// if found entity not used anymore, clean it and return that as "new"
    for(int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
    {
        if(world.EntitiesComponentsMasks[i] == UtilConstants::NO_COMPONENTS) //then a corrispondent position in the components array already exist
        {
            FreeWorldFields(world, i);
            return i;
        }
    }
    
	// else create a new one
    world.EntitiesComponentsMasks.push_back(UtilConstants::NO_COMPONENTS);
    world.EntitiesComponentsMatrix.push_back(std::map<unsigned long int, ComponentBase*>());

	unsigned long int indexNewEntity = world.EntitiesComponentsMasks.size() - 1;
	AddComponent(world, indexNewEntity, new EntityFlag(world, indexNewEntity, flags));
    
    return indexNewEntity; //return size because you want to return an index that points to a newest entity
}

GameObject& EntityManager::GetGameObject(World& world, unsigned long int entityIndex)
{
	return *world.EntitiesHandles[entityIndex];
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

void EntityManager::DeleteAllComponentsForEntity(World& world, unsigned long int entityIndex)
{
	std::map<unsigned long int, ComponentBase*>& entityMap = world.EntitiesComponentsMatrix[entityIndex];
	auto iterComp = entityMap.begin();
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
		std::string methodName = _FUNCTION_NAME_;
		std::ostringstream oss;
		oss << "you're trying to delete a handle that doesn't exist, since entityIndex=" << entityIndex << " could not be found!";
		Utils::PrintDebugLog(methodName, oss.str());

		throw 1;
	}

	world.EntitiesHandles.erase(entityIndex);
}

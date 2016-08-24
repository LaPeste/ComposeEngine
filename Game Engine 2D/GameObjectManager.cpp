//#include "stdafx.h"
//#include "GameObjectManager.hpp"
//#include "Engine.hpp"
//#include "GameObject.hpp"
//
//std::map<long, GameObject*> GameObjectManager::gameObjects;
//std::vector<CollisionEvent> GameObjectManager::collisionEvents;
//const std::string GameObjectManager::TmxIdStringField("GameManager_ID");
//long GameObjectManager::maxIdEverAssigned(0);
//long GameObjectManager::playerId(0);
//
//void GameObjectManager::Init()
//{ 
//    //populates the list of objects with objects coming from the map (tmx file)
//    std::vector<tmx::MapLayer>& layers = Engine::GetInstance().GetMapLoader().GetLayers();
//    for(std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
//    {
//        if(layer->name == Constants::COLLISION_LAYER)
//        {
//            for(std::vector<tmx::MapObject>::iterator object = layer->objects.begin(); object != layer->objects.end(); ++object)
//            {
//                //TODO most likely here I need to do more checks, because I may not want to add all the objects in this layer
//                GameObject* objToAdd = new GameObject( &(*object), 0.0f, 0.0f, GameObjectFlag::MAPONLY);
//                Add(objToAdd);
//            }
//            
//        }
//    }
//    
//    //DEBUG
////    layers = Engine::GetInstance().GetMapLoader().GetLayers();
////    for(std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
////    {
////        for(std::vector<tmx::MapObject>::iterator object = layer->objects.begin(); object != layer->objects.end(); ++object)
////        {
////            std::cout << "name: " << object->GetName() << ", id: " << object->GetPropertyString(TmxIdStringField) << std::endl;
////        }
////    }
//}
//
//GameObjectManager::~GameObjectManager()
//{
//#ifdef LOG_OUTPUT_CONSOLE
//    Utils::PrintDebugLog("~GameObjectManager()", "dctr called");
//#endif
//    
//    for(std::map<long, GameObject*>::iterator mapItem = gameObjects.begin(); mapItem != gameObjects.end(); ++mapItem)
//    {
//        mapItem->second->OnExit();
//    }
//    
//	std::for_each(gameObjects.begin(), gameObjects.end(), GameObjectDeallocator());
//}
//
//void GameObjectManager::Add(GameObject* gameObject)
//{
//    if(gameObject->GetGameObjectType() == GameObjectType::UserPlayer)
//    {
//        playerId = gameObject->GetID();
//    }
//    gameObjects.insert(std::pair<long, GameObject*>(gameObject->GetID(), gameObject));
//}
//
//void GameObjectManager::Remove(long id)
//{
//    std::map<long, GameObject*>::iterator result = gameObjects.find(id);
//	if (result != gameObjects.end())
//	{
//		delete result->second;
//		gameObjects.erase(result);
//	}
//}
//
//void GameObjectManager::ProcessAllCollisions()
//{
//    for(std::vector<CollisionEvent>::iterator collisionEvent = collisionEvents.begin(); collisionEvent != collisionEvents.end(); ++collisionEvent)
//    {
//        if(collisionEvent->entityA == nullptr && collisionEvent->entityB == nullptr) continue;
//        
//        if(collisionEvent->entityA->OnCollision(collisionEvent->entityB))
//        {
//            collisionEvent->entityB->OnCollision(collisionEvent->entityA);
//        }
//    }
//    collisionEvents.clear();
//}
//
//void GameObjectManager::ProcessAllInput(sf::Event event)
//{
//    for(std::map<long, GameObject*>::iterator mapItem = gameObjects.begin(); mapItem != gameObjects.end(); ++mapItem)
//    {
//        mapItem->second->OnEvent(event);
//    }
//}
//
//GameObject* GameObjectManager::GetGameObject(long id)
//{
//	std::map<long, GameObject*>::const_iterator result = gameObjects.find(id);
//	if (result == gameObjects.end())
//	{
//		return NULL;
//	}
//
//	return result->second;
//}
//
//Player* GameObjectManager::GetPlayer()
//{
//    std::map<long, GameObject*>::const_iterator result = gameObjects.find(playerId);
//	if (result == gameObjects.end())
//	{
//		return NULL;
//	}
//
//	return (Player* const)result->second;
//}
//
//const long GameObjectManager::GetUniqueID()
//{
//    long id = maxIdEverAssigned;
//    maxIdEverAssigned++;
//    return id;
//}
//
//const std::vector<CollisionEvent>& GameObjectManager::GetCollisionEvents()
//{
//    return collisionEvents;
//}
//
//u_long GameObjectManager::Count()
//{
//	return gameObjects.size();
//}
//
//void GameObjectManager::DrawAll(sf::RenderWindow& window)
//{
//	std::map<long, GameObject*>::const_iterator itr = gameObjects.begin(); // a const_iterator doesn't allow you to change the values that they point to, regular iterators do.
//
//	while (itr != gameObjects.end())
//	{
//		itr->second->Draw(window);
//		itr++;
//	}
//}
//
//void GameObjectManager::UpdateAll()
//{
//	std::map<long, GameObject*>::const_iterator itr = gameObjects.begin();
//	while (itr != gameObjects.end())
//	{
//		itr->second->Update();
//		itr++;
//	}
//    ProcessAllCollisions();
//}
//
////void GameObjectManager::ProcessAllInput()
////{
////	std::map<GameObjectType, GameObject*>::const_iterator itr = gameObjects.begin();
////	while (itr != gameObjects.end())
////	{
////		itr->second->OnEvent();
////		itr++;
////	}
////}
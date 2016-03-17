#include "stdafx.h"
#include "GameObjectManager.h"
#include "Engine.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	std::for_each(gameObjects.begin(), gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(GameObjectType type, GameObject* gameObject)
{
	gameObjects.insert(std::pair<GameObjectType, GameObject*>(type, gameObject));
}

void GameObjectManager::Remove(GameObjectType type)
{
	std::map<GameObjectType, GameObject*>::iterator results = gameObjects.find(type);
	if (results != gameObjects.end())
	{
		delete results->second;
		gameObjects.erase(results);
	}
}

GameObject* GameObjectManager::Get(GameObjectType type) const
{
	std::map<GameObjectType, GameObject*>::const_iterator results = gameObjects.find(type);
	if (results == gameObjects.end())
	{
		return NULL;
	}

	return results->second;
}

Player* GameObjectManager::GetPlayer() const
{
	std::map<GameObjectType, GameObject*>::const_iterator results = gameObjects.find(GameObjectType::player);
	if (results == gameObjects.end())
	{
		return NULL;
	}

	return (Player* const)results->second;
}

int GameObjectManager::Count() const
{
	return gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& window)
{
	std::map<GameObjectType, GameObject*>::const_iterator itr = gameObjects.begin(); // a const_iterator doesn't allow you to change the values that they point to, regular iterators do.

	while (itr != gameObjects.end())
	{
		itr->second->Draw(window);
		itr++;
	}
}

void GameObjectManager::UpdateAll()
{
	//std::iterator<GameObject> begin = 
	std::map<GameObjectType, GameObject*>::const_iterator itr = gameObjects.begin();
	while (itr != gameObjects.end())
	{
		itr->second->Update();
		itr++;
	}
}

//void GameObjectManager::ProcessAllInput()
//{
//	std::map<GameObjectType, GameObject*>::const_iterator itr = gameObjects.begin();
//	while (itr != gameObjects.end())
//	{
//		itr->second->OnEvent();
//		itr++;
//	}
//}
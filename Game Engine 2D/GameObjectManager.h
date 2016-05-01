#ifndef _GAMEOBJECT_MANAGER_H_
#define _GAMEOBJECT_MANAGER_H_

#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"

class GameObjectManager
{

public:
//	GameObjectManager();
    ~GameObjectManager();

	enum GameObjectType
	{
		player, enemy
	};
	static void Add(GameObjectType Type, GameObject* gameObject);
	static void Remove(GameObjectType type);
	static GameObject* GetGameObject(GameObjectType type);
	static Player* GetPlayer();
	static u_long Count();
	static void DrawAll(sf::RenderWindow& window);
	static void UpdateAll();
	//void ProcessAllInput();

private:
	static std::map<GameObjectType, GameObject*> gameObjects;
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<GameObjectType, GameObject*>& p) const
		{
			if (p.second != nullptr)
			{
				delete p.second;
			}
		}
	};

};

#endif
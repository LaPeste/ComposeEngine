#ifndef _GAMEOBJECT_MANAGER_H_
#define _GAMEOBJECT_MANAGER_H_

#include "stdafx.h"
#include "GameObject.h"
#include "Player.h"

class GameObjectManager
{

public:
	GameObjectManager();
	~GameObjectManager();

	enum GameObjectType
	{
		player, enemy
	};
	void Add(GameObjectType Type, GameObject* gameObject);
	void Remove(GameObjectType type);
	GameObject* Get(GameObjectType type) const;
	Player* GetPlayer() const;
	int Count() const;
	void DrawAll(sf::RenderWindow& window);
	void UpdateAll();
	//void ProcessAllInput();

private:
	std::map<GameObjectType, GameObject*> gameObjects;
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
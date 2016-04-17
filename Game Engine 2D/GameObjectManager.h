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
	GameObject* GetGameObject(GameObjectType type) const;
	Player* GetPlayer() const;
	u_long Count() const;
	void DrawAll(sf::RenderWindow& window) const;
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
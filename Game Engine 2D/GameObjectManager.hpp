//#ifndef _GAMEOBJECT_MANAGER_HPP_
//#define _GAMEOBJECT_MANAGER_HPP_
//
//#include "stdafx.h"
//#include "GameObject.hpp"
//#include "Player.hpp"
//#include "CollisionEvent.hpp"
//
//class GameObjectManager
//{
//
//public:
//    ~GameObjectManager();
//
//    static void Init();
//    static void Add(GameObject* gameObject);
//    static void Remove(long id);
//	static GameObject* GetGameObject(long id);
//	static Player* GetPlayer();
//    static const std::vector<CollisionEvent>& GetCollisionEvents();
//    static const long GetUniqueID();
//	static u_long Count();
//	static void DrawAll(sf::RenderWindow& window);
//	static void UpdateAll();
//	//void ProcessAllInput();
//    static std::vector<CollisionEvent> collisionEvents; //TODO change back to private and find a way to use the getter
//    static const std::string TmxIdStringField;
//    static void ProcessAllCollisions();
//    static void ProcessAllInput(sf::Event event);
//    static void ProcessAllExit();
//    
//private:
//    static std::map<long, GameObject*> gameObjects;
//    static long maxIdEverAssigned;
//    static long playerId;
//    
//	struct GameObjectDeallocator
//	{
//        void operator()(const std::pair<long, GameObject*> & p) const
//		{
//			if (p.second != nullptr)
//			{
//				delete p.second;
//			}
//		}
//	};
//};
//
//#endif
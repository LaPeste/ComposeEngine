#include "GameObject.hpp"
#include "Engine.hpp"
#include "Player.hpp"
#include "EntityManager.hpp"

GameObject::GameObject() : world(nullptr), entityIndex(-1)
{
}

const unsigned long int GameObject::GetEntityIndex() const
{
	return entityIndex;
}

World& GameObject::GetWorld() const
{
	return *world;
}

//void GameObject::RegisterClassForReflection()
//{
//#ifdef REGISTER_GAMEOBJECT
//	World& world = Engine::GetInstance().World;
//	AddClassForReflection(world);
//#endif
//}
//
//void GameObject::AddClassForReflection(World& world)
//{
//	std::cout << "****************************hello***************************" << std::endl;
//	World& world = GetWorld();
//	if (world.EntitiesRegistry.find(typeid(*this).name()) == world.EntitiesRegistry.end())
//	{
//		std::function<unsigned long int(World*)> f = std::bind(&GameObject::Instantiate, this, &world);
//		world.EntitiesRegistry.insert(std::make_pair(typeid(*this).name(), f));
//	}
//}
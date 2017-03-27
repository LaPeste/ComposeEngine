#include "GameObject.hpp"
#include "Engine.hpp"
#include "Player.hpp"
#include "EntityManager.hpp"

GameObject::GameObject()
{
}

unsigned long int GameObject::Instantiate(World* world)
{
	this->world = world;
	entityIndex = EntityManager::CreateEntity(*world, GameObjectFlag::GRAVITY);
	if (typeid(*this) == typeid(Player)) EntityManager::SetPlayerId(entityIndex);

#ifdef LOG_OUTPUT_CONSOLE
	std::stringstream ss;
	ss << "GameObject " << typeid(*this).name() << " with id " << entityIndex << " has been instantiated!";
	std::string s = ss.str();
	std::string methodName = _FUNCION_NAME_;
	Utils::PrintDebugLog(methodName, s);
#endif

	Init();
	return entityIndex;
}

unsigned long int GameObject::GetEntityIndex() const
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
//	if (world.ReflectionMap.find(typeid(*this).name()) == world.ReflectionMap.end())
//	{
//		std::function<unsigned long int(World*)> f = std::bind(&GameObject::Instantiate, this, &world);
//		world.ReflectionMap.insert(std::make_pair(typeid(*this).name(), f));
//	}
//}
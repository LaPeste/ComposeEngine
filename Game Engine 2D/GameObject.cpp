#include "GameObject.hpp"
#include "Engine.hpp"
#include "Player.hpp"
#include "EntityManager.hpp"

GameObject::GameObject() : world(nullptr), entityIndex(-1), EventListener()
{
}

GameObject::~GameObject()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
	Utils::PrintDebugLog(methodName, "dctr called");
#endif
}

const unsigned long int GameObject::GetEntityIndex() const
{
	return entityIndex;
}

World& GameObject::GetWorld() const
{
	return *world;
}

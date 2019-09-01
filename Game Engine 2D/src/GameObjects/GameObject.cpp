#include "GameObjects/GameObject.hpp"
#include "Engine.hpp"
#include "GameObjects/Player.hpp"
#include "Entities/EntityManager.hpp"

GameObject::GameObject() : world(nullptr), entityIndex(-1), EventListener()
{
}

GameObject::~GameObject()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
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

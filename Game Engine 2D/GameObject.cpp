#include "GameObject.hpp"
#include "Engine.hpp"
#include "Player.hpp"
#include "EntityManager.hpp"

GameObject::GameObject() : world(nullptr), entityIndex(-1), EventListener()
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
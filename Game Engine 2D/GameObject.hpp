#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "stdafx.h"
#include "ClassRegistry.hpp"
#include "EventListener.hpp"
#include "Component.hpp"

using namespace Registry;

/*!
 * Classes that inherit from GameObjects are not supposed to be instantiated by new!
 * All you need to do override Init(...) to "define" your gameobject, which in turn is defining what components to add to the
 * entity through the Init.
 */

class GameObject : public EventListener
{
public:
	const unsigned long int GetEntityIndex() const;
	World& GetWorld() const;
	
	template<typename T>
	T* GetComponent();

	template<typename T>
	bool HasComponent();

protected:
	GameObject();
	virtual ~GameObject();

	//! Add here all the components that define the entity, like a prefab in Unity
	virtual void Init() = 0;

private:
	//Friend classes are needed to access ~GameObject(). This allows me to keep the destructor protected, hence not callable by the user.
	friend class EntityManager;
	friend class World;

	unsigned long int entityIndex;
	World* world; //I'd have preferred to have this const :(
};

template<typename T>
T* GameObject::GetComponent()
{
	if (world->EntitiesHandles.find(entityIndex) == world->EntitiesHandles.end())
	{
		throw("Something went very wrong. There was no index " + std::to_string(entityIndex) + " for the this gameObject.");
	}

	return world->GetComponent<T>(entityIndex);
}

template<typename T>
bool GameObject::HasComponent()
{
	auto componentId = Component<T>::Id;

	//0 is the default value for components'Id, if it's zero means the component was never created until now. It's like it doesn't exist, yet.
	return (componentId != 0 && ((world.EntitiesComponentsMasks[entityIndex] & componentId) == componentId));
}


#endif
#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "stdafx.h"
#include "ClassRegistry.hpp"
#include "EventListener.hpp"

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



#endif
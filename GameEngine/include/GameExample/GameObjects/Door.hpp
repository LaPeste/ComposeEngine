#ifndef _DOOR_HPP_
#define _DOOR_HPP_

#include "stdafx.h"
#include "Engine.hpp"
#include "GameObjects/GameObject.hpp"

class Door : public GameObject
{
public:
	void Init() override; //add all the components that define the entity, like a prefab in Unity
};

GAMEOBJECT_REGISTER(Door, "Door", Engine::CurrentWorld)

#endif
#ifndef _DOOR_HPP_
#define _DOOR_HPP_

#include "stdafx.h"
#include "GameObject.hpp"

class Door : public GameObject
{
	void Init() override; //add all the components that define the entity, like a prefab in Unity
};

#endif
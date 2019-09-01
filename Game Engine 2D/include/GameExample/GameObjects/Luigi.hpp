#ifndef _LUIGI_HPP_
#define _LUIGI_HPP_

#include "stdafx.h"
#include "GameObjects/GameObject.hpp"
#include "Engine.hpp"

class Luigi : public GameObject
{
public:
	void Init() override;
};

GAMEOBJECT_REGISTER(Luigi, "Luigi", Engine::CurrentWorld)

#endif
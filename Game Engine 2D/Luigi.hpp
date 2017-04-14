#ifndef _LUIGI_HPP_
#define _LUIGI_HPP_

#include "stdafx.h"
#include "GameObject.hpp"
#include "Engine.hpp"

class Luigi : public GameObject
{
public:
	void Init() override;
};

namespace Registry
{
	GAMEOBJECT_REGISTER(Luigi, "Luigi", Engine::World)
}

#endif
#ifndef _ENTITY_UTILS_HPP_
#define _ENTITY_UTILS_HPP_

#include "stdafx.h"
#include "World.hpp"

namespace Entity
{
	bool HasComponent(World& world, const unsigned long int entityIndex, const unsigned long int componentId);
}

#endif
#ifndef _MAP_OBJECT_SYSTEM_HPP_
#define _MAP_OBJECT_SYSTEM_HPP_

#include "stdafx.h"
#include "System.hpp"
#include "Collider.hpp"

//The Appearance component is used because it acts as a transform

class MapObjectSystem : public System<Collider, Appearance>
{
public:
	MapObjectSystem(World& world);

private:
	void LateUpdate(World& world, const unsigned long int entityIndex) override;
};

#endif
#ifndef _COLLISION_DETECTOR_HPP_
#define __COLLISION_DETECTOR_HPP_

#include "stdafx.h"
#include "System.hpp"

class CollisionDetector : public System<Collider>
{
public:
	CollisionDetector(World& world);

private:
	void LateUpdate(World& world, const unsigned long int  entityIndex) override;
};

#endif /* __COLLISION_DETECTOR_HPP_ */
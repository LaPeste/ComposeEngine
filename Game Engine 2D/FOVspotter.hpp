#ifndef _FOV_SPOTTER_HPP_
#define _FOV_SPOTTER_HPP_

#include "stdafx.h"
#include "System.hpp"

class FOVspotter : public System<Collider, FieldOfView>
{
public:
	FOVspotter(World& world);

private:
	void LateUpdate(World& world, const unsigned long int  entityIndex) override;
};

#endif /* _FOV_SPOTTER_HPP_ */
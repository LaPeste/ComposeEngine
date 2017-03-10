#ifndef _MAP_OBJECT_HPP_
#define _MAP_OBJECT_HPP_

#include "stdafx.h"
#include "Component.hpp"

class MapObjectComponent : public Component<MapObjectComponent>
{
public:
	MapObjectComponent();

	bool NeedsUpdate() const;
	void SetToUpdate(const bool state);

private:
	bool modified;
};

#endif
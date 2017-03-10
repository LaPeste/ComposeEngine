#include "MapObjectComponent.hpp"

MapObjectComponent::MapObjectComponent() : modified(false)
{
}

bool MapObjectComponent::NeedsUpdate() const
{
	return modified;
}

void MapObjectComponent::SetToUpdate(const bool state)
{
	modified = state;
}
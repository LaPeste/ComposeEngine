#include "EntityUtils.hpp"

bool HasComponent(World& world, const unsigned long int entityIndex, const unsigned long int componentId)
{
	//0 is the default value for components'Id, if it's zero means the component was never created until now. It's like it doesn't exist, yet.
	return (componentId != 0 && ((world.EntitiesComponentsMasks[entityIndex] & componentId) == componentId));
}
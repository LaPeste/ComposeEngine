#include "ClassRegistry.hpp"

namespace Registry
{
	EntitiesRegistry& GetGameObjectsRegistry()
	{
		static EntitiesRegistry GameObjectsRegistry;
		return GameObjectsRegistry;
	}
}
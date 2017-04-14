#include "ClassRegistry.hpp"

namespace Registry
{
	EntitiesRegistry& GetGameObjectsRegistry()
	{
		static EntitiesRegistry GameObjectsRegistry;
		return GameObjectsRegistry;
	}

	//const RegistryEntry<TYPE>& GameObjectRegistration<TYPE>::reg = RegistryEntry<TYPE>::Instance(NAME, WORLD);			
}
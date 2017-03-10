#include "MapObjectSystem.hpp"

MapObjectSystem::MapObjectSystem(World& world) : System<Collider, Appearance>(world)
{

}

void MapObjectSystem::LateUpdate(World& world, const unsigned long int entityIndex)
{
	std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
	if (entity[MapObjectComponent::Id] == nullptr)
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "no MapObjectComponent was found for the element" << entityIndex;
		Utils::PrintDebugError(methodName, oss.str());
		throw 1;
	}

	
	Collider* collider = static_cast<Collider*>(entity[Component<Collider>::Id]);
	Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);

	//TODO for now I don't see the reason to add this, maybe in the future I'll realise it's needed
	/*if (!collider->CopyDataToMapObject(world, i))
	{
		std::string methodName = _FUNCION_NAME_;
		Utils::PrintDebugError(methodName, "it was not possible to copy collider data to the relative MapObject");
		throw 1;
	}*/
	if (!appearance->CopyDataToMapObject(world, entityIndex))
	{
		std::string methodName = _FUNCION_NAME_;
		Utils::PrintDebugError(methodName, "it was not possible to copy transform data to the relative MapObject");
		throw 1;
	}
	
}
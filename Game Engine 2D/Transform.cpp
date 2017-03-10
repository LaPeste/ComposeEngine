#include "Transform.hpp"
#include "Appearance.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"

Transform::Transform() : position()
{
	
}

const sf::Vector2f& Transform::GetPosition(World& world, unsigned const long entityIndex) const
{
	std::map<unsigned long int, ComponentBase*>& entityComponents = world.EntitiesComponentsMatrix[entityIndex];
	const Appearance* appearance = static_cast<const Appearance*>(entityComponents[Appearance::Id]);

	if (appearance == nullptr)
	{
		return position;
	}

	//if it has a sprite
	return appearance->GetSprite()->getPosition();
}

void Transform::SetPosition(World& world, unsigned const long entityIndex, const sf::Vector2f& pos)
{
	std::map<unsigned long int, ComponentBase*>& entityComponents = world.EntitiesComponentsMatrix[entityIndex];
	Appearance* appearance = static_cast<Appearance*>(entityComponents[Appearance::Id]);

	if (entityComponents[Appearance::Id] == nullptr)
	{
		position = pos;
	}
	else
	{
		appearance->GetSprite()->setPosition(pos.x, pos.y);
	}
}

//super expensive method!
bool Transform::CopyDataToMapObject(World& world, const unsigned long int entityIndex)
{
	std::map<unsigned long int, ComponentBase*>& entityComponents = world.EntitiesComponentsMatrix[entityIndex];
	const Transform* transform = static_cast<const Transform*>(entityComponents[Transform::Id]);

	//TODO try to cache the objects parsed from the map otherwise it'll be very expensive everytime that data are copied
	//TODO try also to find a way to mark variables as dirty so that this method won't do anything if not dirty
	std::vector<tmx::MapLayer>& layers = Engine::GetInstance().GetMapLoader().getLayers();
	for (std::vector<tmx::MapLayer>::iterator layer = layers.begin(); layer != layers.end(); ++layer)
	{
		if (layer->name == Constants::COLLISION_LAYER)
		{
			for (std::vector<tmx::MapObject>::iterator object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				if (entityIndex == std::stoi(object->getPropertyString(Constants::ENTITY_INDEX_PROPERTY)))
				{
					object->setPosition(transform->GetPosition(world, entityIndex));
					return true;
				}
			}
		}
	}
	return false;

}
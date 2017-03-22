#include "Transform.hpp"
#include "Appearance.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"

Transform::Transform(World& world, const unsigned long int entityIndex) : transformable(), Component(world, entityIndex)
{
	
}

Transform::~Transform() {}

const sf::Vector2f& Transform::GetPosition() const
{
	if (Entity::HasComponent(world, entityIndex, Appearance::Id))
	{
		std::map<unsigned long int, ComponentBase*>& entityComponents = world.EntitiesComponentsMatrix[entityIndex];
		Appearance* appearance = static_cast<Appearance*>(entityComponents[Appearance::Id]);
		return appearance->GetSprite()->getPosition();
	}

	//if it has a sprite
	return transformable.getPosition();
}

void Transform::SetPosition(const sf::Vector2f& pos)
{

	if (Entity::HasComponent(world, entityIndex, Appearance::Id))
	{
		std::map<unsigned long int, ComponentBase*>& entityComponents = world.EntitiesComponentsMatrix[entityIndex];
		Appearance* appearance = static_cast<Appearance*>(entityComponents[Appearance::Id]);
		appearance->GetSprite()->setPosition(pos.x, pos.y);
	}
	else
	{
		transformable.setPosition(pos);
	}
}

const sf::Transform& Transform::GetTransform() const
{
	if (Entity::HasComponent(world, entityIndex, Appearance::Id))
	{
		std::map<unsigned long int, ComponentBase*>& entityComponents = world.EntitiesComponentsMatrix[entityIndex];
		Appearance* appearance = static_cast<Appearance*>(entityComponents[Appearance::Id]);
		return appearance->GetSprite()->getTransform();
	}

	return transformable.getTransform();
}
#include "Components/Transform.hpp"
#include "Components/Appearance.hpp"
#include "tmx/MapLoader.hpp"
#include "Engine.hpp"
#include "Entities/EntityManager.hpp"
#include "MathLib.hpp"
#include "GameObjects/GameObject.hpp"

Transform::Transform(World& world, const unsigned long int entityIndex) : 
	Component(world, entityIndex),
	m_sprite(nullptr)
{
	
}

Transform::~Transform() {}

sf::Vector2f Transform::GetUpDir()
{
	auto upDir = TransformPoint(0, -1) - TransformPoint(0, 0);

	// normalization needed if the entity is scaled
	if (GetSprite()->getScale() != sf::Vector2f(1, 1))
	{
		upDir = MathLib::Normalize(upDir);
	}
	return upDir;
}

sf::Vector2f Transform::GetForwardDir()
{
	auto fwDir = TransformPoint(1, 0) - TransformPoint(0, 0);

	// normalization needed if the entity is scaled
	if (GetSprite()->getScale() != sf::Vector2f(1, 1))
	{
		fwDir = MathLib::Normalize(fwDir);
	};
	return fwDir;
}

sf::Sprite* Transform::GetSprite()
{
	if (m_sprite == nullptr)
	{
		auto& gameObject = EntityManager::GetGameObject(world, entityIndex);
		auto* appearance = gameObject.GetComponent<Appearance>();
		assert(appearance && "A unit without appearance was found. It's a disaster.");
		m_sprite = appearance->GetSprite();
		const auto& topLeftPos = m_sprite->getPosition();
		const float halfWidth = m_sprite->getLocalBounds().width / 2;
		const float halfHeight = m_sprite->getLocalBounds().height / 2;
		auto newOrigin = sf::Vector2f(topLeftPos.x + halfWidth, topLeftPos.y + halfHeight);
		m_sprite->setOrigin(newOrigin);
	}
	return m_sprite;
}

const sf::Vector2f& Transform::GetPosition()
{
	auto* m_sprite = GetSprite();
	return m_sprite->getPosition();
}

void Transform::SetPosition(const sf::Vector2f& pos)
{
	auto* m_sprite = GetSprite();
	m_sprite->setPosition(pos);
}

sf::Vector2f Transform::TransformPoint(float x, float y)
{
	auto* m_sprite = GetSprite();
	return m_sprite->getTransform().transformPoint(x, y);
}

sf::Vector2f Transform::TransformPoint(const sf::Vector2f& point)
{
	auto* m_sprite = GetSprite();
	return m_sprite->getTransform().transformPoint(point);
}

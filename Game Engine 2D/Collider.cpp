//
//  Collider.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 02/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Collider.hpp"
#include "Transform.hpp"
#include "Appearance.hpp"

Collider::Collider(World& world, const unsigned long int entityIndex, const sf::Vector2f& offset, const sf::FloatRect& colliderRect) :
	offset(offset), colliderRect(colliderRect),
	Component(world, entityIndex)
{
    
}

Collider::~Collider() {}


const sf::FloatRect& Collider::GetColliderRect() const
{
	if (Entity::HasComponent(world, entityIndex, Appearance::Id))
	{
		Appearance* appearance = static_cast<Appearance*>(world.EntitiesComponentsMatrix[entityIndex][Appearance::Id]);
		if (appearance->IsTextureLoaded())
		{
			return appearance->GetSprite()->getGlobalBounds();
		}
		else
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream oss;
			oss << "Texture isn't loaded so there's no Collider Rectangle to obtain for unit " << entityIndex;
			Utils::PrintDebugError(methodName, oss.str());
		}
	}
	return colliderRect;
}

std::vector<sf::Vector2f> Collider::GetCollisionPoints() const
{
    std::vector<sf::Vector2f> collisionPoints;
	if (Entity::HasComponent(world, entityIndex, Transform::Id))
	{
		const sf::Transform& trans = (static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]))->GetTransform();
		sf::FloatRect local = GetColliderRect();
		collisionPoints.push_back(sf::Vector2f{ trans.transformPoint(0.f - offset.x, 0.f - offset.y) });
		collisionPoints.push_back(sf::Vector2f{ trans.transformPoint(local.width + offset.x, 0 - offset.y) });
		collisionPoints.push_back(sf::Vector2f{ trans.transformPoint(local.width + offset.x, local.height + offset.y) });
		collisionPoints.push_back(sf::Vector2f{ trans.transformPoint(0 - offset.x, local.height + offset.y) });
	}
	else    //I don't see how there could not be a transform... but just in case
	{
		collisionPoints.push_back(sf::Vector2f{ -offset.x, -offset.y });
		collisionPoints.push_back(sf::Vector2f{ offset.x, -offset.y });
		collisionPoints.push_back(sf::Vector2f{ -offset.x, offset.y });
		collisionPoints.push_back(sf::Vector2f{ offset.x, offset.y });
	}
    
    return collisionPoints;
}

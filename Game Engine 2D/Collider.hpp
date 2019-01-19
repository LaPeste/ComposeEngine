//
//  Collider.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 02/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COLLIDER_HPP_
#define _COLLIDER_HPP_

#include "stdafx.h"
#include "Component.hpp"
#include <unordered_set>

using EntityCollisions = std::unordered_set<unsigned long>;

class Collider : public Component<Collider>
{
public:
    Collider(World& world, const unsigned long int entityIndex, const sf::Vector2f& offset = sf::Vector2f(0, 0), const sf::FloatRect& colliderRect = sf::FloatRect());
	~Collider() override;
    
	// getters
	const sf::FloatRect& GetColliderRect() const;

	/*! 
	 * Returns a set of points in world space defining the borders of the collider,
	 * the one adherent to the sprite size.
	 * The returning 4 points are ordered as follow:
	 * - top left,
	 * - top right,
	 * - bottom right
	 * - bottom left,
	 */
	std::vector<sf::Vector2f> GetCollisionPoints() const;

	/*!
	* Returns a set of points in world space defining the borders of the collider ready for physics
	* which is following the offset given at construction time.
	* The returning 4 points are ordered as follow:
	* - top left,
	* - top right,
	* - bottom right
	* - bottom left,
	*/
	std::vector<sf::Vector2f> GetPhysicsCollisionPoints() const;
	EntityCollisions& GetEnityCollisions();

private:
    sf::Vector2f offset;
	sf::FloatRect colliderRect;
	EntityCollisions m_entityToEntityCollisions;
};

#endif /* _COLLIDER_HPP_ */

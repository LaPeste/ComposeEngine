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

class Collider : public Component<Collider>
{
public:
    Collider(World& world, const unsigned long int entityIndex, const sf::Vector2f& offset = sf::Vector2f(0, 0), const sf::FloatRect& colliderRect = sf::FloatRect());
	~Collider() override;
    
	const sf::FloatRect& GetColliderRect() const;

	//returns a set of points in world space defining the borders of the collider
    std::vector<sf::Vector2f> GetCollisionPoints() const;

private:
    sf::Vector2f offset;
	sf::FloatRect colliderRect;
};

#endif /* _COLLIDER_HPP_ */

//
//  Collider.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 02/10/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Collider.hpp"

Collider::Collider(const sf::Vector2f& offset) : offset(offset), 
Component()
{
    
}

std::vector<sf::Vector2f> Collider::GetCollisionPoints(const Appearance& appearance) const
{
    std::vector<sf::Vector2f> collisionPoints;
    collisionPoints.push_back(sf::Vector2f{ 0 - offset.x, 0 - offset.y });
    collisionPoints.push_back(sf::Vector2f{ appearance.GetSprite()->getLocalBounds().width + offset.x, 0 - offset.y });
    collisionPoints.push_back(sf::Vector2f{ 0 - offset.x, appearance.GetSprite()->getLocalBounds().height + offset.y });
    collisionPoints.push_back(sf::Vector2f{ appearance.GetSprite()->getLocalBounds().width + offset.x, appearance.GetSprite()->getLocalBounds().height + offset.y });
    
    return collisionPoints;
}

std::vector<sf::Vector2f> Collider::GetCollisionPoints() const
{
    std::vector<sf::Vector2f> collisionPoints;
    collisionPoints.push_back(sf::Vector2f{ -offset.x, -offset.y });
    collisionPoints.push_back(sf::Vector2f{ offset.x, -offset.y });
    collisionPoints.push_back(sf::Vector2f{ -offset.x, offset.y });
    collisionPoints.push_back(sf::Vector2f{ offset.x, offset.y });
    
    return collisionPoints;
}

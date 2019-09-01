#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "stdafx.h"
#include "Components/Component.hpp"

/*
 If an Appearance component exists, then the sf::Sprite transform is returned, otherwise the private sf::Transformable of this class is return.
*/

class Transform : public Component<Transform>
{
public:
	Transform(World& world, const unsigned long int entityIndex);
	~Transform() override;

	//! Return position of top left corner
	const sf::Vector2f& GetPosition();
	sf::Sprite* GetSprite();
	sf::Vector2f GetUpDir();
	sf::Vector2f GetForwardDir();

	/*! 
	 * Returns true and writes position of center of the sprite in parameter.
	 * False is returned if no appearance component exists for this entity.
	 */
	//bool GetCenteredPosition(sf::Vector2f& outVector);
	void SetPosition(const sf::Vector2f& pos);
	sf::Vector2f TransformPoint(float x, float y);
	sf::Vector2f TransformPoint(const sf::Vector2f& pos);
	//TODO add functions for getting and setting rotation, scale etc...

private:
	sf::Sprite* m_sprite;
};

#endif
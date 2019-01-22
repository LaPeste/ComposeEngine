#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "stdafx.h"
#include "Component.hpp"

/*
 If an Appearance component exists, then the sf::Sprite transform is returned, otherwise the private sf::Transformable of this class is return.
*/

class Transform : public Component<Transform>
{
public:
	Transform(World& world, const unsigned long int entityIndex);
	~Transform() override;

	const sf::Vector2f& GetPosition() const;
	void SetPosition(const sf::Vector2f& pos);
	sf::Vector2f TransformPoint(float x, float y) const;
	//TODO add functions for getting and setting rotation, scale etc...

private:
	sf::Transformable transformable;
};

#endif
#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Transform : public Component<Transform>
{
public:
	Transform(World& world, const unsigned long int entityIndex);
	~Transform();

	const sf::Vector2f& GetPosition() const;
	void SetPosition(const sf::Vector2f& pos);
	const sf::Transform& GetTransform() const;
	//TODO add functions for getting and setting rotation, scale etc...

private:
	sf::Transformable transformable;
};

#endif
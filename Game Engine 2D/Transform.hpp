#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Transform : public Component<Transform>
{
public:
	Transform();

	const sf::Vector2f& GetPosition(World& world, unsigned const long entityIndex) const;
	void SetPosition(World& world, unsigned const long entityIndex, const sf::Vector2f& pos);

	bool CopyDataToMapObject(World& world, const unsigned long int entityIndex) override;

private:
	sf::Vector2f position;
};

#endif
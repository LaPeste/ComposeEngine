#ifndef _FIELD_OF_VIEW_HPP_
#define _FIELD_OF_VIEW_HPP_

#include "stdafx.h"
#include "Component.hpp"

class FieldOfView : public Component<FieldOfView>
{
public:
	FieldOfView(World& world, const uint32_t entityIndex, float radius, float degrees, const sf::Vector2f& direction/*, const std::unordered_set<type_info>& enemyTypes*/);

	float GetRadius() const;
	float GetDegrees() const;
	const sf::Vector2f& GetDirection() const;
	

	std::vector<const GameObject*> GetEnemies() const;

	//! Tells if an enemy was spotted the frame before the current one.
	bool IsEnemySpotted() const;

	bool IsEnemy(const GameObject& objToEvaluate) const;
	void SetSpottedEnemy(bool value);

private:
	const float m_radius;
	const float m_degrees;
	const sf::Vector2f m_direction;

	bool m_spottedEnemy;
	std::vector<const GameObject*> m_enemies;
	//const std::unordered_set<type_info> m_enemyTypes;

};

#endif //_FIELD_OF_VIEW_HPP_
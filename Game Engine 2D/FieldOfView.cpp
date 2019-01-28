#include "FieldOfView.hpp"
#include "Player.hpp"

FieldOfView::FieldOfView(World& world, const uint32_t entityIndex, float radius, float degrees, const sf::Vector2f& direction/*, const std::unordered_set<type_info>& enemyTypes*/) :
	Component<FieldOfView>(world, entityIndex),
	m_radius(radius), m_direction(direction), m_degrees(degrees),
	m_spottedEnemy(false)/*, m_enemyTypes(enemyTypes)*/
{
	for (auto& currGameObject : world.EntitiesHandles)
	{
		if (typeid(*currGameObject.second) == typeid(Player))
		{
			m_enemies.push_back(currGameObject.second);
			break;
		}
	}
}

float FieldOfView::GetRadius() const
{
	return m_radius;
}

float FieldOfView::GetDegrees() const
{
	return m_degrees;
}

bool FieldOfView::IsEnemy(const GameObject& objToEvaluate) const
{
	for (auto* currEnemy : m_enemies)
	{
		if (typeid(objToEvaluate) == typeid(*currEnemy)) return true;
	}
	return false;
}

std::vector<const GameObject*> FieldOfView::GetEnemies() const
{
	/*if (m_enemies.size() == 0)
	{
		for (auto& currGameObject : world.EntitiesHandles)
		{
			if (typeid(currGameObject.second) == typeid(Player))
			{
				m_enemies.push_back(currGameObject.second);
				break;
			}
		}
	}*/
	return m_enemies;
}

const sf::Vector2f& FieldOfView::GetDirection() const
{
	return m_direction;
}
//const std::unordered_set<type_info> FieldOfView::GetEnemyTypes() const
//{
//	return m_enemyTypes;
//}

bool FieldOfView::IsEnemySpotted() const
{
	return m_spottedEnemy;
}

void FieldOfView::SetSpottedEnemy(bool value)
{
	m_spottedEnemy = value;
}
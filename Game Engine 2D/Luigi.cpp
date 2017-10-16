#include "Luigi.hpp"
#include "EntityManager.hpp"
#include "Appearance.hpp"
#include "Acceleration.hpp"
#include "Animation.hpp"
#include "Controller.hpp"
#include "EntityFlag.hpp"
#include "Velocity.hpp"
#include "Collider.hpp"
#include "Transform.hpp"
#include "BehaviourTree.hpp"

void Luigi::Init()
{
	World& world = GetWorld();
	const unsigned long int entityIndex = GetEntityIndex();
	EntityManager::AddComponent(world, entityIndex, new Appearance(world, entityIndex, Constants::RESOURCE_PATH + Constants::PLAYER_SPRITE_PATH));
	Appearance* appearance = static_cast<Appearance*>(world.EntitiesComponentsMatrix[entityIndex][Appearance::Id]);
	sf::IntRect spriteRect(498, 12, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
	appearance->GetSprite()->setTextureRect(spriteRect);
	EntityManager::AddComponent(world, entityIndex, new Transform(world, entityIndex));
	Transform* trans = static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]);
	trans->SetPosition(sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X + 30, Constants::PLAYER_PHYSICAL_STARTING_Y + 87));
	EntityManager::AddComponent(world, entityIndex, new Collider(world, entityIndex, sf::Vector2f(0, 0), sf::FloatRect(trans->GetPosition().x, trans->GetPosition().y, 20, 20)));
	EntityManager::AddComponent(world, entityIndex, new Acceleration(world, entityIndex, Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y));
	EntityManager::AddComponent(world, entityIndex, new Controller(world, entityIndex));
	EntityManager::AddComponent(world, entityIndex, new Velocity(world, entityIndex));
	//EntityManager::AddComponent(world, entityIndex, new BT::BehaviourTree(world, entityIndex, /*pass test tree*/));
}
#include "GameExample/GameObjects/Luigi.hpp"
#include "Entities/EntityManager.hpp"
#include "Components/Appearance.hpp"
#include "Components/Acceleration.hpp"
#include "Animations/Animation.hpp"
#include "Components/Controller.hpp"
#include "Components/EntityFlag.hpp"
#include "Components/Velocity.hpp"
#include "Components/Collider.hpp"
#include "Components/Transform.hpp"
#include "GameExample/AI/Patrolling.hpp"
#include "AI/BasicNodes/Repeater.hpp"
#include "Components/FieldOfView.hpp"

void Luigi::Init()
{
	World& world = GetWorld();
	const unsigned long int entityIndex = GetEntityIndex();

	sf::IntRect spriteRect(498, 12, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
	EntityManager::AddComponent(world, entityIndex, new Appearance(world, entityIndex, Constants::RESOURCE_PATH + Constants::PLAYER_SPRITE_PATH, spriteRect));

	EntityManager::AddComponent(world, entityIndex, new Transform(world, entityIndex));
	Transform* trans = static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]);
	trans->SetPosition(sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X + 30, Constants::PLAYER_PHYSICAL_STARTING_Y + 87));
	EntityManager::AddComponent(world, entityIndex, new Collider(world, entityIndex, sf::Vector2f(0, 0), sf::FloatRect(trans->GetPosition().x, trans->GetPosition().y, 20, 20)));
	EntityManager::AddComponent(world, entityIndex, new Acceleration(world, entityIndex, Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y));
	EntityManager::AddComponent(world, entityIndex, new Controller(world, entityIndex));
	EntityManager::AddComponent(world, entityIndex, new Velocity(world, entityIndex));
	EntityManager::AddComponent(world, entityIndex, new FieldOfView(world, entityIndex, 100.f, 45.f, sf::Vector2f(1,0)));

	/*BT::BehaviourTree* bt = new BT::BehaviourTree(world, entityIndex, *this);
	std::unique_ptr<BT::Repeater> rootRepeater = std::make_unique<BT::Repeater>(nullptr, std::vector<std::unique_ptr<BT::Node>>(), *bt);
	std::unique_ptr<BT::Patrolling> patrNode = std::make_unique<BT::Patrolling>(rootRepeater.get(), std::vector<std::unique_ptr<BT::Node>>(), *bt);
	rootRepeater->AddChild(std::move(patrNode));
	bt->SetRoot(std::move(rootRepeater));
	EntityManager::AddComponent(world, entityIndex, bt);*/
}
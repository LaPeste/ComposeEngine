//
//  Player.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Player.hpp"
#include "EntityManager.hpp"

//Components
#include "Appearance.hpp"
#include "Acceleration.hpp"
#include "Animation.hpp"
#include "Controller.hpp"
#include "EntityFlag.hpp"
#include "Velocity.hpp"
#include "Collider.hpp"
#include "Transform.hpp"

//Events
#include "InputEvent.hpp"
#include "Animations.hpp"

void Player::Init()
{
	World& world = GetWorld();
	const unsigned long int entityIndex = GetEntityIndex();

	std::string playerSpritePath = Constants::RESOURCE_PATH + Constants::PLAYER_SPRITE_PATH;
	sf::IntRect spriteRect(498, 12, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
	EntityManager::AddComponent(world, entityIndex, new Appearance(world, entityIndex, playerSpritePath, spriteRect));

	EntityManager::AddComponent(world, entityIndex, new Transform(world, entityIndex));
    //(static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]))->SetPosition(sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y));
    GetComponent<Transform>()->SetPosition(sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y));

    EntityManager::AddComponent(world, entityIndex, new Acceleration(world, entityIndex, Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y));
	Controller* controllerComp = new Controller(world, entityIndex);
    EntityManager::AddComponent(world, entityIndex, controllerComp);
    EntityManager::AddComponent(world, entityIndex, new Velocity(world, entityIndex));
    EntityManager::AddComponent(world, entityIndex, new Collider(world, entityIndex, sf::Vector2f(0.5f, 0.5f)));
    

	//Animation states - start
	const auto* const playerSprite = GetComponent<Appearance>()->GetSprite();
    std::map<AnimationState, AnimationData*> animationMap;
    AnimationData* walkingAnim = new AnimationData(playerSprite, sf::Vector2f(Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y),
                           sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
                           false, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE);
    
    animationMap.insert( std::pair<AnimationState, AnimationData*>(AnimationState::WALKING, walkingAnim) );

	AnimationData* idleAnim = new AnimationData(playerSprite, sf::Vector2f(14, 10),
		sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
		false, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, 1, Constants::ANIMATION_FRAMERATE);

	animationMap.insert(std::pair<AnimationState, AnimationData*>(AnimationState::IDLE, idleAnim));

	AnimationData* jumpAnim = new AnimationData(playerSprite, sf::Vector2f(115, 7),
		sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
		false, 16, Constants::PLAYER_HEIGHT, 1, Constants::ANIMATION_FRAMERATE);

	animationMap.insert(std::pair<AnimationState, AnimationData*>(AnimationState::JUMPING, jumpAnim));
	//Animation states - end

	Animation* animationComp = new Animation(world, entityIndex, AnimationState::IDLE, animationMap, true);
    EntityManager::AddComponent(world, entityIndex, animationComp);

	OnGameEvent<InputEvent>([&world, entityIndex](Event<InputEvent>* i) {

		if (i != nullptr)
		{
			auto* castedEvent = static_cast<InputEvent*>(i);
			Animations::BasicInputAnimation(world, entityIndex, *castedEvent);
		}
		else
		{
			DEBUG_WARNING("The event passed was null!");
		}
	});
    
}
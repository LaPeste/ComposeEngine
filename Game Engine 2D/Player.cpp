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
	EntityManager::AddComponent(world, entityIndex, new Appearance(world, entityIndex, Constants::RESOURCE_PATH + Constants::PLAYER_SPRITE_PATH));
	EntityManager::AddComponent(world, entityIndex, new Transform(world, entityIndex));
    (static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]))->SetPosition(sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y));
    
    EntityManager::AddComponent(world, entityIndex, new Acceleration(world, entityIndex, Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y));
	Controller* controllerComp = new Controller(world, entityIndex);
    EntityManager::AddComponent(world, entityIndex, controllerComp);
    EntityManager::AddComponent(world, entityIndex, new Velocity(world, entityIndex));
    EntityManager::AddComponent(world, entityIndex, new Collider(world, entityIndex));
    

	//Animation states
    std::map<AnimationState, AnimationData*> animationMap;
    AnimationData* walkingAnim = new AnimationData(sf::Vector2f(Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y),
                           sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
                           false, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE);
    
    animationMap.insert( std::pair<AnimationState, AnimationData*>(AnimationState::WALKING, walkingAnim) );

	AnimationData* idleAnim = new AnimationData(sf::Vector2f(14, 10),
		sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
		false, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, 1, Constants::ANIMATION_FRAMERATE);

	animationMap.insert(std::pair<AnimationState, AnimationData*>(AnimationState::IDLE, idleAnim));

	AnimationData* jumpAnim = new AnimationData(sf::Vector2f(115, 7),
		sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
		false, 16, /*22*/Constants::PLAYER_HEIGHT, 1, Constants::ANIMATION_FRAMERATE);

	animationMap.insert(std::pair<AnimationState, AnimationData*>(AnimationState::JUMPING, jumpAnim));

	Animation* animationComp = new Animation(world, entityIndex, AnimationState::IDLE, animationMap, true);
    EntityManager::AddComponent(world, entityIndex, animationComp);
	
	//std::function<void(InputEvent*)> leftMethod = [&animationComp](InputEvent* i) { if(i->GetMessage() == InputEventType::RIGHT_DOWN) animationComp->CurrentAnimationState = AnimationState::WALKING; };
	//FMS(sort of) for animation, basically listening for events will trigger changes in AnimationState
	OnGameEvent<InputEvent>([&world, entityIndex](InputEvent* i) {
		if(i != nullptr) Animations::BasicInputAnimation(world, entityIndex, *i);
	});
    
}
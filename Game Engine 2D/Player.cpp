//
//  Player.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Player.hpp"
#include "EntityManager.hpp"
#include "Engine.hpp"
#include "TransformUtils.hpp"
#include "Appearance.hpp"
#include "Acceleration.hpp"
#include "Animation.hpp"
#include "Controller.hpp"
#include "EntityFlag.hpp"
#include "Velocity.hpp"
#include "Collider.hpp"
#include "Collider.hpp"
#include "Transform.hpp"

Player::Player()
{
    World& world = Engine::GetInstance().World;
    const unsigned long entityIndex = EntityManager::CreateEntity(world);
    EntityManager::SetPlayerId(entityIndex); //TODO: this should be automated in the EntityManager...

	EntityManager::AddComponent(world, entityIndex, new Appearance(Constants::RESOURCE_PATH + Constants::PLAYER_SPRITE_PATH));
	EntityManager::AddComponent(world, entityIndex, new Transform());
    (static_cast<Transform*>(world.EntitiesComponentsMatrix[entityIndex][Transform::Id]))->SetPosition(world, entityIndex, sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y));
    
    EntityManager::AddComponent(world, entityIndex, new Acceleration(Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y));
    EntityManager::AddComponent(world, entityIndex, new Controller());
    EntityManager::AddComponent(world, entityIndex, new EntityFlag(GameObjectFlag::GRAVITY));
    EntityManager::AddComponent(world, entityIndex, new Velocity());
    EntityManager::AddComponent(world, entityIndex, new Collider(sf::Vector2f(0,0)));
//    world.EntitiesComponentsMasks[entityIndex] = ;
//    world.ComponentMap[entityIndex] = ;
    
    //world.EntitiesComponentsMasks[entityIndex] | Components::APPEARANCE | Components::ACCELERATION | Components::CONTROLLER | Components::FLAG |
    //Components::POSITION | Components::VELOCITY | Components::ANIMATION | Components::COLLIDER;
    
//    world.Appearance[entityIndex] = new Appearance(Constants::PLAYER_SPRITE_PATH);
//    TransformUtils::SetPosition(world, entityIndex, sf::Vector2f(Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y));
//    world.Acceleration[entityIndex] = new Acceleration(Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y);
//    world.Controller[entityIndex] = new Controller;
//    world.EntityFlag[entityIndex] = new EntityFlag(GameObjectFlag::GRAVITY);
//    world.Velocity[entityIndex] = new Velocity;
//    world.Collider[entityIndex] = new Collider(sf::Vector2f(0,0));
    
    std::map<AnimationState, AnimationData*> animationMap;
    AnimationData* animData = new AnimationData(sf::Vector2f(Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y),
                           sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
                           false, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE);
    
    animationMap.insert( std::pair<AnimationState, AnimationData*>(AnimationState::IDLE, animData) );
    
    EntityManager::AddComponent(world, entityIndex, new Animation(AnimationState::IDLE , animationMap, true));
    
//    world.Collision[entityIndex] = new Collision;
}

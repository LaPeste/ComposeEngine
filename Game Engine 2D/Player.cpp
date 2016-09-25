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

Player::Player()
{
    World& world = Engine::GetInstance().World;
    const unsigned long entityIndex = EntityManager::CreateEntity(world);
    EntityManager::SetPlayerId(entityIndex); //TODO: this should be automated in the EntityManager...
    
    world.EntitiesMasks[entityIndex] = world.EntitiesMasks[entityIndex] | Components::APPEARANCE | Components::ACCELERATION | Components::CONTROLLER | Components::FLAG |
    Components::POSITION | Components::VELOCITY | Components::ANIMATION;
    world.Appearance[entityIndex] = new Appearance(Constants::PLAYER_SPRITE_PATH);
    world.Acceleration[entityIndex] = new Acceleration(Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y);
    world.Controller[entityIndex] = new Controller;
    world.EntityFlag[entityIndex] = new EntityFlag(GameObjectFlag::GRAVITY);
    world.Position[entityIndex] = new Position(world, entityIndex, Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y, true);
    world.Velocity[entityIndex] = new Velocity;
    
    std::map<AnimationState, AnimationData> animationMap;
    AnimationData animData(sf::Vector2f(Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y),
                           sf::Vector2f(Constants::SPACE_BETWEEN_SPRITE_X, Constants::SPACE_BETWEEN_SPRITE_Y), false,
                           false, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE);
    animationMap.insert( std::pair<AnimationState, AnimationData>(AnimationState::IDLE, animData) );
    world.Animation[entityIndex] = new Animation(AnimationState::IDLE , animationMap, true);
    
//    world.Collision[entityIndex] = new Collision;
}
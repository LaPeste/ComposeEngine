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
        Components::POSITION | Components::VELOCITY;
    world.Appearance[entityIndex] = new Appearance(Constants::PLAYER_SPRITE_PATH, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE, false,
                                               Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
    world.Acceleration[entityIndex] = new Acceleration(Constants::PLAYER_MAX_ACCELERATION_X, Constants::PLAYER_MAX_ACCELERATION_Y);
    world.Controller[entityIndex] = new Controller;
    world.EntityFlag[entityIndex] = new EntityFlag(GameObjectFlag::GRAVITY);
    world.Position[entityIndex] = new Position(world, entityIndex, Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y, true);
    world.Velocity[entityIndex] = new Velocity;
//    world.Collision[entityIndex] = new Collision;
}
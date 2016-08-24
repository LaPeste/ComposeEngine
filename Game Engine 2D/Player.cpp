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
    EntityManager::SetPlayerId(entityIndex);
    
//    *world.EntitiesMasks[entityIndex] = Components::APPEARANCE;
    world.EntitiesMasks[entityIndex] = Components::APPEARANCE;
    world.Appearance[entityIndex] = new Appearance(Constants::PLAYER_SPRITE_PATH, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE, false,
                                               Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
}
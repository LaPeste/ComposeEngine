//
//  CollisionDetection.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "CollisionDetection.hpp"
#include "Camera.hpp"
#include "Engine.hpp"
#include "Appearance.hpp"
#include "Position.hpp"
#include <tmx/MapObject.h>
#include "EntityManager.hpp"

bool CollisionDetection::Collides(const World& world, const unsigned long index)
{
    Appearance& appearance = *world.Appearance[index];
    Position& position = *world.Position[index];
    
    sf::FloatRect rootNode(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetWidth(), Camera::GetInstance()->GetHeight());
    Engine::GetInstance().GetMapLoader().UpdateQuadTree(rootNode); //update quadtree's rootnode to what's visible in the screen
    std::vector<tmx::MapObject*> objects = Engine::GetInstance().GetMapLoader().QueryQuadTree(appearance.GetSprite()->getGlobalBounds()); // grab all the MapObjects contained in the quads intersected by the bounds of sprite
    if(!Engine::GetInstance().GetMapLoader().QuadTreeAvailable())
    {
        Utils::PrintDebugError("Collides()", "No MapTree to query is available");
        return false;
    }
    bool collision = false;

    for(auto object = objects.begin(); object != objects.end(); ++object)
    {
        if((*object)->GetParent() == Constants::COLLISION_LAYER)
        {
//            const std::vector<const sf::Vector2f&>* const collisionPoints = CalculateCollisionPoint(world, index);
            
            std::vector<sf::Vector2f> collisionPoints;
            collisionPoints.push_back(sf::Vector2f{0, 0});
            collisionPoints.push_back(sf::Vector2f{appearance.GetSprite()->getLocalBounds().width, 0});
            collisionPoints.push_back(sf::Vector2f{0, appearance.GetSprite()->getLocalBounds().height});
            collisionPoints.push_back(sf::Vector2f{appearance.GetSprite()->getLocalBounds().width, appearance.GetSprite()->getLocalBounds().height});
            
            for(int i = 0; i < 4; i++) //where 4 is the amount of collisionPoints we have. Those are the 4 corners of the sprite of a gameObject.
            {
                collision = (*object)->Contains(position.GetPosition(world, index) + collisionPoints[i]);

                if(collision) break;
            }
//            delete collisionPoints;
        }
        if(collision)
        {
//            std::cout << "addr " << ((void*)&(*object)) << " , property " << GameObjectManager::TmxIdStringField << ": " << (*object)->GetPropertyString(GameObjectManager::TmxIdStringField) << ", name: " << (*object)->GetName() << std::endl;
            
            //TODO check how to treat objects coming from the tmx map
            if((*object)->GetPropertyString(Constants::ENTITY_INDEX_PROPERTY) != "")
            {
                const unsigned long searchId = std::stol((*object)->GetPropertyString(Constants::ENTITY_INDEX_PROPERTY));
                Components entity = world.EntitiesMasks[searchId];
//                if(mapGameObject != nullptr && mapGameObject->GetGameObjectType() == GameObjectType::MapCollisionObject)
//                {
//                    CollisionEvent coll(this, mapGameObject);
//                    GameObjectManager::collisionEvents.push_back(coll); //TODO try to get this list through its getter
//                }
                if((entity & COLLISION_MASK) == (COLLISION_MASK) && (world.EntityFlag[searchId]->GetEntityFlag() & GameObjectFlag::MAP_OBJECT) == (GameObjectFlag::MAP_OBJECT))
                {
                    CollisionEvent coll(index, searchId);
                    EntityManager::AddCollisionEvent(coll);
                }
            }
            break;
        }
    }

    return collision;
}

//const std::vector<const sf::Vector2f&>* const CollisionDetection::CalculateCollisionPoint(const World& world, const unsigned long entityIndex)
//{
//    Appearance& appearance = *world.Appearance[entityIndex];
//    
//    std::vector<const sf::Vector2f&>* const collisionPoints = new std::vector<const sf::Vector2f&>;
//    collisionPoints->push_back(sf::Vector2f{0, 0});
//    collisionPoints->push_back(sf::Vector2f{appearance.GetSprite()->getGlobalBounds().width, 0});
//    collisionPoints->push_back(sf::Vector2f{0, appearance.GetSprite()->getGlobalBounds().height});
//    collisionPoints->push_back(sf::Vector2f{appearance.GetSprite()->getGlobalBounds().width, appearance.GetSprite()->getGlobalBounds().height});
//    
//    return collisionPoints;
//}
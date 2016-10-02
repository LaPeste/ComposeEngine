//
//  CollisionDetection.cpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "CollisionDetectionUtils.hpp"
#include "Camera.hpp"
#include "Engine.hpp"
#include "Appearance.hpp"
#include "TransforUtils.hpp"
#include <tmx/MapObject.h>
#include "EntityManager.hpp"

bool CollisionDetectionUtils::Collides(const World& world, const unsigned long index)
{
//    EntityFlag& entityFlag = *world.EntityFlag[index];
    Appearance& appearance = *world.Appearance[index];
    Collider& collider = *world.Collider[index];
    
    sf::FloatRect rootNode(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetWidth(), Camera::GetInstance()->GetHeight());
    Engine::GetInstance().GetMapLoader().UpdateQuadTree(rootNode); //update quadtree's rootnode to what's visible in the screen
    std::vector<tmx::MapObject*> objects = Engine::GetInstance().GetMapLoader().QueryQuadTree(appearance.GetSprite()->getGlobalBounds()); // grab all the MapObjects contained in the quads intersected by the bounds of sprite
    if(!Engine::GetInstance().GetMapLoader().QuadTreeAvailable())
    {
        Utils::PrintDebugError("Collides()", "No MapTree to query is available");
        return false;
    }
    bool collision = false;

    std::vector<sf::Vector2f> collisionPoints;
    if((world.EntitiesMasks[index] & Components::APPEARANCE) == (Components::APPEARANCE) )
    {
        collisionPoints = collider.GetCollisionPoints(appearance);
    }
    else
    {
        collisionPoints = collider.GetCollisionPoints();
    }
    
    unsigned long searchId;
    for(auto object = objects.begin(); object != objects.end(); ++object)
    {
        searchId = std::stol((*object)->GetPropertyString(Constants::ENTITY_INDEX_PROPERTY));
        if((*object)->GetParent() == Constants::COLLISION_LAYER && (world.EntitiesMasks[searchId] & Components::COLLIDER) == Components::COLLIDER)
        {
            for(int i = 0; i < 4; i++) //where 4 is the amount of collisionPoints we have. Those are the 4 corners of the sprite of a gameObject.
            {
                collision = (*object)->Contains(TransformUtils::GetPosition(world, index) + collisionPoints[i]);

                if(collision) break;
            }
        }
        if(collision)
        {
//            if((*object)->GetName() != "Ground")
//            Utils::PrintDebugLog("Collides", "object " + (*object)->GetName() + " with " + Constants::ENTITY_INDEX_PROPERTY + ": " + (*object)->GetPropertyString(Constants::ENTITY_INDEX_PROPERTY));
            //TODO check how to treat objects coming from the tmx map
            if((*object)->GetPropertyString(Constants::ENTITY_INDEX_PROPERTY) != "")
            {
                
//                Components entity = world.EntitiesMasks[searchId];
//                if(mapGameObject != nullptr && mapGameObject->GetGameObjectType() == GameObjectType::MapCollisionObject)
//                {
//                    CollisionEvent coll(this, mapGameObject);
//                    GameObjectManager::collisionEvents.push_back(coll); //TODO try to get this list through its getter
//                }
//                if((world.EntitiesMasks[index] & Components::COLLIDER) == (Components::COLLIDER) && (world.EntityFlag[searchId]->GetEntityFlag() & GameObjectFlag::MAP_OBJECT) == (GameObjectFlag::MAP_OBJECT))
//                   )
//                {
                    CollisionEvent coll(index, searchId);
                    EntityManager::AddCollisionEvent(coll);
//                }
            }
            break;
        }
    }

    return collision;
}
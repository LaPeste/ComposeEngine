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
#include "Collider.hpp"
#include "Transform.hpp"
#include "tmx/MapObject.hpp"
#include "EntityManager.hpp"

//TODO theoretically here world should be constant since we are just checking for collision and not modifying world, but... I can't get the code to work if it is set to be const
bool CollisionDetectionUtils::Collides(World& world, const unsigned long index)
{
    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[index];
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);
	Collider* collider = static_cast<Collider*>(entity[Component<Collider>::Id]);
	Transform* transform = static_cast<Transform*>(entity[Transform::Id]);
    
    sf::FloatRect rootNode(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetWidth(), Camera::GetInstance()->GetHeight());
    Engine::GetInstance().GetMapLoader().updateQuadTree(rootNode); //update quadtree's rootnode to what's visible on the screen
	
	//grab all the MapObjects contained in the quads intersected by the bounds of sprite
    std::vector<tmx::MapObject*> mapObjects = Engine::GetInstance().GetMapLoader().queryQuadTree(appearance->GetSprite()->getGlobalBounds());
    if(!Engine::GetInstance().GetMapLoader().quadTreeAvailable())
    {
		std::string methodName = _FUNCION_NAME_;
        Utils::PrintDebugError(methodName, "No MapTree to query is available");
        return false;
    }
    bool collision = false;

    std::vector<sf::Vector2f> collisionPoints;
    if((world.EntitiesComponentsMasks[index] & Component<Appearance>::Id) == Component<Appearance>::Id )
    {
        collisionPoints = collider->GetCollisionPoints(*appearance);
    }
    else
    {
        collisionPoints = collider->GetCollisionPoints();
    }
    
    unsigned long searchId;
    for(auto object = mapObjects.begin(); object != mapObjects.end(); ++object)
    {
        searchId = std::stol((*object)->getPropertyString(Constants::ENTITY_INDEX_PROPERTY));
        if((*object)->getParent() == Constants::COLLISION_LAYER && (world.EntitiesComponentsMasks[searchId] & Component<Collider>::Id) == Component<Collider>::Id)
        {
            for(int i = 0; i < 4; i++) //where 4 is the amount of collisionPoints we have. Those are the 4 corners of the sprite of a gameObject.
            {
                collision = (*object)->contains(transform->GetPosition(world, index) + collisionPoints[i]);

                if(collision) break;
            }
        }
        if(collision)
        {
//            if((*object)->GetName() != "Ground")
//            Utils::PrintDebugLog("Collides", "object " + (*object)->GetName() + " with " + Constants::ENTITY_INDEX_PROPERTY + ": " + (*object)->GetPropertyString(Constants::ENTITY_INDEX_PROPERTY));
            //TODO check how to treat objects coming from the tmx map
            if((*object)->getPropertyString(Constants::ENTITY_INDEX_PROPERTY) != "")
            {
                
//                Components entity = world.EntitiesComponentsMasks[searchId];
//                if(mapGameObject != nullptr && mapGameObject->GetGameObjectType() == GameObjectType::MapCollisionObject)
//                {
//                    CollisionEvent coll(this, mapGameObject);
//                    GameObjectManager::collisionEvents.push_back(coll); //TODO try to get this list through its getter
//                }
//                if((world.EntitiesComponentsMasks[index] & Components::COLLIDER) == (Components::COLLIDER) && (world.EntityFlag[searchId]->GetEntityFlag() & GameObjectFlag::MAP_OBJECT) == (GameObjectFlag::MAP_OBJECT))
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

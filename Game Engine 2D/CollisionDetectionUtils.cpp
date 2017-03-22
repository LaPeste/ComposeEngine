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

#include <cmath>

//TODO try make world a constant reference check task https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/9944030/
bool CollisionDetectionUtils::Collides(World& world, const unsigned long index)
{
	if ((world.EntitiesComponentsMasks[index] & Collider::Id) != Collider::Id) return false;

    std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[index];
    Appearance* appearance = static_cast<Appearance*>(entity[Component<Appearance>::Id]);
	Collider* collider = static_cast<Collider*>(entity[Component<Collider>::Id]);
	Transform* transform = static_cast<Transform*>(entity[Transform::Id]);
    
    sf::FloatRect rootNode(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetWidth(), Camera::GetInstance()->GetHeight());
	//update quadtree's rootnode to what's visible on the screen
    Engine::GetInstance().GetMapLoader().updateQuadTree(rootNode);
	
	//grab all the MapObjects contained in the quads intersected by the bounds of sprite
    std::vector<tmx::MapObject*> mapObjects = Engine::GetInstance().GetMapLoader().queryQuadTree(collider->GetColliderRect());
    if(!Engine::GetInstance().GetMapLoader().quadTreeAvailable())
    {
		std::string methodName = _FUNCION_NAME_;
        Utils::PrintDebugError(methodName, "No MapTree to query is available");
        return false;
    }

    std::vector<sf::Vector2f> collisionPoints = collider->GetCollisionPoints();
    
    bool mapCollision = false;

    for(auto mapObject = mapObjects.begin(); mapObject != mapObjects.end(); ++mapObject)
    {
        if((*mapObject)->getParent() == Constants::COLLISION_LAYER)
        {
            for(int i = 0; i < 4; i++) //where 4 is the amount of collisionPoints we have. Those are the 4 corners of the sprite of a gameObject.
            {
                mapCollision = (*mapObject)->contains(collisionPoints[i]);

                if(mapCollision) break;
            }
			if (mapCollision) break;
        }
    }

	bool entityCollision = false;
	//Engine entities
	for (int i = 0; i < world.EntitiesComponentsMasks.size(); ++i)
	{
		//TODO	check freedcamp task for improving collision detection https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/9943624/
		if (i == index) continue;

		entityCollision = BoundingBoxTest(world, index, i);
		if (entityCollision)
		{
			CollisionEvent coll(index, i);
			EntityManager::AddCollisionEvent(coll);

			break; //TODO what if collides with more objects? When the todo tasks right above is fixed then
				   // we can leave it check for all possible collisions with the subset of possible (close) collider entites
		}
		
	}

    return mapCollision || entityCollision;
}


/****************************/

/*
* What's below is adapted from work of
* Author: Nick (original version), ahnonay (SFML2 compatibility)
*/

class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
	OrientedBoundingBox(std::vector<sf::Vector2f> collisionPoints) : CollisionPoints(collisionPoints) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
	{}

	std::vector<sf::Vector2f> CollisionPoints;

	//Min and Max are the lenght of the projections, on a parallel axis, of the min and max edge of the box under examination
	//there is a good amount of mathematical equalitis in stating that "projA = vecA dotProduct axis"
	//The best reference I have for explaining it can be found at https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169
	void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
	{
		Min = (CollisionPoints[0].x*Axis.x + CollisionPoints[0].y*Axis.y);
		Max = Min;
		for (int j = 1; j<4; j++)
		{
			float Projection = (CollisionPoints[j].x*Axis.x + CollisionPoints[j].y*Axis.y);

			if (Projection<Min)
				Min = Projection;
			if (Projection>Max)
				Max = Projection;
		}
	}
};

bool CollisionDetectionUtils::BoundingBoxTest(World& world, unsigned long int entity1, unsigned long int entity2) {
	if ((((world.EntitiesComponentsMasks[entity1] & Collider::Id) != Collider::Id) || ((world.EntitiesComponentsMasks[entity1] & Transform::Id) != Transform::Id)) ||
		(((world.EntitiesComponentsMasks[entity2] & Collider::Id) != Collider::Id) || ((world.EntitiesComponentsMasks[entity2] & Transform::Id) != Transform::Id)))
	{
		return false;
	}
	OrientedBoundingBox OBB1((static_cast<Collider*>(world.EntitiesComponentsMatrix[entity1][Collider::Id]))->GetCollisionPoints());
	OrientedBoundingBox OBB2((static_cast<Collider*>(world.EntitiesComponentsMatrix[entity2][Collider::Id]))->GetCollisionPoints());

	// Create the four distinct axes that are perpendicular to the edges of the two rectangles
	sf::Vector2f Axes[4] = {
		sf::Vector2f(OBB1.CollisionPoints[1].x - OBB1.CollisionPoints[0].x,
		OBB1.CollisionPoints[1].y - OBB1.CollisionPoints[0].y),
		sf::Vector2f(OBB1.CollisionPoints[1].x - OBB1.CollisionPoints[2].x,
		OBB1.CollisionPoints[1].y - OBB1.CollisionPoints[2].y),
		sf::Vector2f(OBB2.CollisionPoints[0].x - OBB2.CollisionPoints[3].x,
		OBB2.CollisionPoints[0].y - OBB2.CollisionPoints[3].y),
		sf::Vector2f(OBB2.CollisionPoints[0].x - OBB2.CollisionPoints[1].x,
		OBB2.CollisionPoints[0].y - OBB2.CollisionPoints[1].y)
	};

	for (int i = 0; i<4; i++) // For each axis...
	{
		float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

		// ... project the points of both OBBs onto the axis ...
		OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
		OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

		// ... and check whether the outermost projected points of both OBBs overlap.
		// If this is not the case, the Seperating Axis Theorem states that there can be no collision between the rectangles
		if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
			return false;
	}
	return true;
}

/****************************/
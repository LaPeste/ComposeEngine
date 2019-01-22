//
//  CollisionDetection.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 04/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _COLLISION_DETECTION_UTILS_HPP_
#define _COLLISION_DETECTION_UTILS_HPP_

#include "stdafx.h"
#include "World.hpp"

class CollisionDetectionUtils
{
public:
    static bool PhysicsCollides(World& world, const unsigned long entityIndex);

	static bool BoundingBoxTestEngineEntities(World& world, unsigned long int entity1, unsigned long int entity2, bool physics = false);

	/* BoundingBoxTest adapted from work of
	* Authors : Nick Koirala(original version), ahnonay(SFML2 compatibility)
	*
	* Collision Detection and handling class
	* For SFML2.
	*/

	/*!
	 * Test for bounding box collision using the Seperating Axis Theorem
	 * Supports scaling and rotation.
	 * All coordinates are supposed to be global!!
	 */
	static bool BoundingBoxTest(std::vector<sf::Vector2f> obj1AABBCoord, std::vector<sf::Vector2f> obj2AABBCoord);

};

#endif /* _COLLISION_DETECTION_UTILS_HPP_ */

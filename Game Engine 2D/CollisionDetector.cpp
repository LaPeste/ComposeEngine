#include "CollisionDetector.hpp"
#include "EntityUtils.hpp"
#include "CollisionDetectionUtils.hpp"
#include "Player.hpp";
#include "Luigi.hpp";

CollisionDetector::CollisionDetector(World& world):
	System<Collider>(world)
{

}

void CollisionDetector::LateUpdate(World& world, const unsigned long int  entityIndex)
{
	Collider* thisCollider = world.GetComponent<Collider>(entityIndex);
	if (thisCollider == nullptr) return;

	// clean from previous frame
	thisCollider->GetEnityCollisions().clear();

	for (int i = 0; i < world.EntitiesComponentsMatrix.size(); ++i)
	{
		// avoid self-test
		if (i == entityIndex) continue;
		if (!Entity::HasComponent(world, i, Collider::Id)) continue;

		// if collision between this and other was found then just register it on this collider
		Collider* otherCollider = world.GetComponent<Collider>(i);
		if (otherCollider == nullptr) continue;
		auto& collisions = otherCollider->GetEnityCollisions();
		if (collisions.find(i) != collisions.end())
		{
			thisCollider->GetEnityCollisions().insert(i);
			continue;
		}

		auto thisGameobj = dynamic_cast<Player*>(world.EntitiesHandles[entityIndex]);
		auto otherGameobj = dynamic_cast<Luigi*>(world.EntitiesHandles[i]);
		if (CollisionDetectionUtils::BoundingBoxTestEngineEntities(world, entityIndex, i))
		{
			thisCollider->GetEnityCollisions().insert(i);

			if (thisGameobj == nullptr || otherCollider == nullptr) continue;
			DEBUG_LOG("collision between Mario and Luigi has happened!");
		}
	}
}
#include "GameExample/Behaviours/Systems/FOVspotter.hpp"
#include "Collisions/CollisionDetectionUtils.hpp"
#include "Components/Transform.hpp"
#include "MathLib.hpp"
#include <iterator>
#include "GameObjects/GameObject.hpp"

FOVspotter::FOVspotter(World& world) :
	System<Collider, FieldOfView>(world)
{

}

// 1- get fov of entity
// 2- do the test on a circle
// 3- if enemy is in bound, then check if it's in fov (by dir and radius of FOV
void FOVspotter::LateUpdate(World& world, const unsigned long int  entityIndex)
{
	auto& gameObject = EntityManager::GetGameObject(world, entityIndex);
	auto* fov = gameObject.GetComponent<FieldOfView>();
	auto* trans = gameObject.GetComponent<Transform>();
	if (fov == nullptr || trans == nullptr) return;

	// clear previous frame data
	fov->SetSpottedEnemy(false);

	sf::Vector2f thisPos = trans->GetPosition();
	const float radius = fov->GetRadius();
	std::vector<sf::Vector2f> collisionPoints;
	//top left
	collisionPoints.push_back(sf::Vector2f(thisPos.x - radius, thisPos.y - radius));
	//top right
	collisionPoints.push_back(sf::Vector2f(thisPos.x + radius, thisPos.y - radius));
	//bottom right
	collisionPoints.push_back(sf::Vector2f(thisPos.x + radius, thisPos.y + radius));
	//bottom left
	collisionPoints.push_back(sf::Vector2f(thisPos.x - radius, thisPos.y + radius));

#ifdef VISUAL_DEBUG
	GeometryDebugger::DrawCircle(thisPos, fov->GetRadius());
	GeometryDebugger::DrawRay(thisPos, trans->GetForwardDir() * 30.f, sf::Color::Black);
	GeometryDebugger::DrawRay(thisPos, trans->GetUpDir() * 30.f, sf::Color::Magenta);
	auto up = MathLib::RotateVector(trans->GetForwardDir(), MathLib::ToRadiants(-fov->GetDegrees() / 2));
	auto down = MathLib::RotateVector(trans->GetForwardDir(), MathLib::ToRadiants(fov->GetDegrees() / 2));
	GeometryDebugger::DrawRay(thisPos, up * 30.f, sf::Color::Green);
	GeometryDebugger::DrawRay(thisPos, down * 30.f, sf::Color::Blue);
#endif // VISUAL_DEBUG

	for (int i = 0; i < world.EntitiesComponentsMatrix.size(); ++i)
	{
		// avoid self-test
		if (i == entityIndex) continue;
		auto& otherGameObj = EntityManager::GetGameObject(world, i);
		auto* otherCollider = otherGameObj.GetComponent<Collider>();
		if (otherCollider == nullptr) continue;


		if (!fov->IsEnemy(otherGameObj)) continue;

		auto otherCollPoints = otherCollider->GetCollisionPoints();
		if (CollisionDetectionUtils::BoundingBoxTest(collisionPoints, otherCollPoints))
		{
			auto* transOther = otherGameObj.GetComponent<Transform>();
			sf::Vector2f otherPos = transOther->GetPosition();
			auto dirToEnemy = otherPos - thisPos;
			auto angle = MathLib::AngleBetween2Vectors(trans->GetForwardDir(), dirToEnemy);

#ifdef VISUAL_DEBUG
		GeometryDebugger::DrawLine(thisPos, otherPos);
#endif // VISUAL_DEBUG

			if (angle >= -fov->GetDegrees() / 2 && angle <= fov->GetDegrees() / 2)
			{
				fov->SetSpottedEnemy(true);
#ifdef VISUAL_DEBUG
				DEBUG_LOG("Enemy in fov");
#endif
				return;
			}
		}
	}
}
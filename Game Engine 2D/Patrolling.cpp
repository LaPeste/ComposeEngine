#include "Patrolling.hpp"
#include "Controller.hpp"
#include "Transform.hpp"

#include "GameObject.hpp"

namespace BT
{
	Patrolling::Patrolling(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		originalPosition(0.0f, 0.0f), finalPosition(0.0f, 0.0f), turnBack(false),
		Node(parent, std::move(children), bt)
	{}

	Status Patrolling::Init()
	{
		GameObject& gameObject = bt->GetGameObjectAssociated();;
		const uint32_t entityIndex = gameObject.GetEntityIndex();
		std::map<unsigned long int, ComponentBase*>& entity = gameObject.GetWorld().EntitiesComponentsMatrix[entityIndex];
		Controller* controller = static_cast<Controller*>(entity[Controller::Id]);
		Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

		originalPosition = transform->GetPosition();
		finalPosition.x = originalPosition.x + 100.0f;
		turnBack = false;
		controller->SetMoveLeft(false);
		controller->SetMoveRight(true);

		status = Status::RUNNING;
		return Status::RUNNING;
	}

	Status Patrolling::Process()
	{
		GameObject& gameObject = bt->GetGameObjectAssociated();;
		const uint32_t entityIndex = gameObject.GetEntityIndex();
		std::map<unsigned long int, ComponentBase*>& entity = gameObject.GetWorld().EntitiesComponentsMatrix[entityIndex];
		Controller* controller = static_cast<Controller*>(entity[Controller::Id]);
		Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

		if (transform->GetPosition().x > originalPosition.x)
		{
			if (!turnBack)
			{
				controller->SetMoveLeft(false);
				controller->SetMoveRight(true);
				turnBack = transform->GetPosition().x > finalPosition.x;
			}
			else
			{
				controller->SetMoveRight(false);
				controller->SetMoveLeft(true);
			}
			status = Status::RUNNING;
			return Status::RUNNING;
		}

		controller->SetMoveRight(false);
		controller->SetMoveLeft(false);

		status = Status::SUCCESS;
		return Status::SUCCESS;
	}
}
#include "Patrolling.hpp"
#include "Controller.hpp"
#include "Transform.hpp"

#include "GameObject.hpp"

namespace BT
{
	Patrolling::Patrolling(std::unique_ptr<Node> parent, std::vector<std::unique_ptr<Node>> children, Context& context) :
		originalPosition(0.0f, 0.0f), finalPosition(0.0f, 0.0f), turnBack(false),
		Node(std::move(parent), std::move(children), context)
	{}

	Patrolling::Patrolling(std::unique_ptr<Node> parent, std::vector<std::unique_ptr<Node>> children) :
		originalPosition(0.0f, 0.0f), finalPosition(0.0f, 0.0f), turnBack(false),
		Node(std::move(parent), std::move(children))
	{}

	Status Patrolling::Init()
	{
		if (context->find("gameObject") == context->end())
		{
			std::string methodName = _FUNCION_NAME_;
			Utils::PrintDebugError(methodName, "Context does not have the field gameObject. Abort!");
			throw 1;
		}
		GameObject* gameObject = static_cast<GameObject*>(context->at("gameObject"));
		//GameObject& gameObject = static_cast<GameObject>(*(context->at("gameObject").get()));
		const uint32_t entityIndex = gameObject->GetEntityIndex();
		std::map<unsigned long int, ComponentBase*>& entity = gameObject->GetWorld().EntitiesComponentsMatrix[entityIndex];
		Controller* controller = static_cast<Controller*>(entity[Controller::Id]);
		Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

		originalPosition = transform->GetPosition();
		finalPosition.x = originalPosition.x + 100.0f;
		controller->SetMoveLeft(false);
		controller->SetMoveRight(true);

		SetStatus(Status::RUNNING);
		return Status::RUNNING;
	}

	Status Patrolling::Process()
	{
		GameObject* gameObject = static_cast<GameObject*>(context->at("gameObject"));
		//GameObject& gameObject = *(reinterpret_cast<GameObject>(context->at("gameObject")));
		const uint32_t entityIndex = gameObject->GetEntityIndex();
		std::map<unsigned long int, ComponentBase*>& entity = gameObject->GetWorld().EntitiesComponentsMatrix[entityIndex];
		Controller* controller = static_cast<Controller*>(entity[Controller::Id]);
		Transform* transform = static_cast<Transform*>(entity[Transform::Id]);

		if (transform->GetPosition().x > originalPosition.x)
		{
			if (!turnBack)
			{
				controller->SetMoveLeft(false);
				controller->SetMoveRight(true);
				controller->SetWantToJump(true);
				turnBack = transform->GetPosition().x > finalPosition.x;
			}
			else
			{
				controller->SetMoveRight(false);
				controller->SetMoveLeft(true);
			}
			SetStatus(Status::RUNNING);
			return Status::RUNNING;
		}

		controller->SetMoveRight(false);
		controller->SetMoveLeft(false);

		SetStatus(Status::SUCCESS);
		return Status::SUCCESS;
	}
}
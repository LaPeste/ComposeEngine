#include "Patrolling.hpp"
#include "Controller.hpp"
#include "Transform.hpp"
#include "Engine.hpp"
#include "Transform.hpp"

#include "GameObject.hpp"

namespace BT
{
	Patrolling::Patrolling(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		m_originalPosition(0.0f, 0.0f), m_finalPosition(0.0f, 0.0f), m_turnBack(false),
		m_entity(nullptr), m_controller(nullptr), m_transform(nullptr),
		Node(parent, std::move(children), bt)
	{
		GameObject& gameObject = bt.GetGameObjectAssociated();
		const uint32_t entityIndex = gameObject.GetEntityIndex();
		m_entity = &(gameObject.GetWorld().EntitiesComponentsMatrix[entityIndex]);
		m_controller = static_cast<Controller*>((*m_entity)[Controller::Id]);
		m_transform = static_cast<Transform*>((*m_entity)[Transform::Id]);
	}

	void Patrolling::Init()
	{
		m_originalPosition = m_transform->GetPosition();
		m_finalPosition.x = m_originalPosition.x + 100.0f;
		m_finalPosition.y = m_originalPosition.y;
		m_turnBack = false;
	}

	void Patrolling::OnProcess()
	{
		if (!m_turnBack && m_transform->GetPosition().x == m_originalPosition.x)
		{
			m_controller->SetMoveLeft(false);
			m_controller->SetMoveRight(true);
		}
		else if (m_transform->GetPosition().x > m_originalPosition.x)
		{
			if (!m_turnBack)
			{
				m_controller->SetMoveLeft(false);
				m_controller->SetMoveRight(true);
				m_turnBack = m_transform->GetPosition().x > m_finalPosition.x;
			}
			else
			{
				m_controller->SetMoveRight(false);
				m_controller->SetMoveLeft(true);
			}
		}
		else if (m_turnBack && m_transform->GetPosition().x <= m_originalPosition.x)
		{
			m_controller->SetMoveRight(false);
			m_controller->SetMoveLeft(false);
			status = Status::SUCCESS;
		}
	}
}
#include "AttackWhenInRange.h"

namespace BT
{
	AttackWhenInRange::AttackWhenInRange(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		m_eyeSightLength(0.0f), Node(parent, std::move(children), bt)
	{

	}

	void AttackWhenInRange::Init()
	{

	}

	void AttackWhenInRange::OnProcess()
	{

	}
}
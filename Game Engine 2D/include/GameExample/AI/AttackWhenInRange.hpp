#ifndef _ATTACK_WHEN_IN_RANGE_HPP_
#define _ATTACK_WHEN_IN_RANGE_HPP_

#include "AI/BehaviourTree.hpp"

namespace BT
{
	class AttackWhenInRange : public Node
	{
	public:
		AttackWhenInRange(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt);

		void Init() override;
		void OnProcess() override;

	private:
		float m_eyeSightLength;
	};
}

#endif
#ifndef _PATROLLING_HPP_
#define _PATROLLING_HPP_

#include "BehaviourTree.hpp"

namespace BT
{
	class Patrolling : public Node
	{
	public:
		Patrolling(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt);

		void Init() override;
		void OnProcess() override;

	private:
		sf::Vector2f originalPosition;
		sf::Vector2f finalPosition;
		bool turnBack;
	};
}

#endif
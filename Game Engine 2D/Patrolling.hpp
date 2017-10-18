#ifndef _PATROLLING_HPP_
#define _PATROLLING_HPP_

#include "BehaviourTree.hpp"

namespace BT
{
	class Patrolling : public Node
	{
	public:
		Patrolling(std::unique_ptr<Node> parent, std::vector<std::unique_ptr<Node>> children, Context& context);
		Patrolling(std::unique_ptr<Node> parent, std::vector<std::unique_ptr<Node>> children);

		Status Init() override;
		Status Process() override;

	private:
		sf::Vector2f originalPosition;
		sf::Vector2f finalPosition;
		bool turnBack;
	};
}

#endif
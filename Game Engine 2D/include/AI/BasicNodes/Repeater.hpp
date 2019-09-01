#ifndef _REPEATER_HPP_
#define _REPEATER_HPP_

#include "AI/BehaviourTree.hpp"

/*!
 * A repeater will reprocess its child node each time its child returns a result.
 * These are often used at the very base of the tree, to make the tree to run continuously
 */

namespace BT
{
	class Repeater : public Node
	{
	public:
		Repeater(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt);
		void Init() override;
		void OnProcess() override;

	private:
	};
}

#endif
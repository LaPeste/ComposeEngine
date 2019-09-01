#ifndef _SELECTOR_HPP_
#define _SELECTOR_HPP_

#include "AI/BehaviourTree.hpp"
/*!
 * As opposite to sequences a selector return a success if any of its children succeed and not process any further children.
 * It will process the first child, and if it fails will process the second, and if that fails will process the third, until a success is reached,
 * at which point it will instantly return success. It will fail if all children fail.
 */
namespace BT
{
	class Selector : public Node
	{
	public:
		Selector(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt);
		void Init() override;
		void OnProcess() override;

	private:
		int currentChildIndex;
	};
}


#endif
#ifndef _SEQUENCE_HPP_
#define _SEQUENCE_HPP_

#include "BehaviourTree.hpp"

/*!
 * A sequence will visit each child in order, starting with the first, and when that succeeds will call the second, and so on down the list of children.
 * If any child fails it will immediately return failure to the parent.
 * If the last child in the sequence succeeds, then the sequence will return success to its parent.
 */


namespace BT
{
	class Sequence : public Node
	{
	public:
		Sequence(Node* parent, std::vector<Node> children);
		Status Init() override;
		Status Process() override;

	private:
		int currentChildIndex;
	};
}


#endif
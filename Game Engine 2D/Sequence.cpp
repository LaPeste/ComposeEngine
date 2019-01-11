#include "Sequence.hpp"

namespace BT
{
	Sequence::Sequence(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		currentChildIndex(0), Node(parent, std::move(children), bt)
	{}

	void Sequence::Init()
	{
		int childrenSize = GetChildren().size();
		if (childrenSize == 0)
		{
			std::string methodName = _FUNCTION_NAME_;
			std::ostringstream oss;
			oss << "There are no children for the selected sequence. Nothing to init.";
			Utils::PrintDebugWarning(methodName, oss.str());
			//TODO not sure it should be like this in case of no children https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/13027290/
		}
	}


	void Sequence::OnProcess()
	{
		int childrenIndexSize = GetChildren().size() - 1;
		Node& currChild = GetChild(currentChildIndex);

		// Init or continue running current child
		if (currChild.GetStatus() == Status::NONE)
		{
			currChild.Init();
			currChild.Process();
		}
		else if (currChild.GetStatus() == Status::FAILURE)
		{
			status = Status::FAILURE;
		}
		else if (currChild.GetStatus() == Status::SUCCESS)
		{
			// if last child
			if (currentChildIndex == childrenIndexSize)
			{
				status = Status::SUCCESS;
			}
			else
			{
				GetChild(++currentChildIndex).Process();
			}
		}
		//the running case is not needed since it will always be taken care by the BTEngine, through currentNode
	}
}
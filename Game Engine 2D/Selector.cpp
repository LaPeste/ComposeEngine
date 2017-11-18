#include "Selector.hpp"

namespace BT
{
	Selector::Selector(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		currentChildIndex(0), Node(parent, std::move(children), bt)
	{}

	void Selector::Init()
	{
		int childrenSize = GetChildren().size();
		if (childrenSize == 0)
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream oss;
			oss << "There are no children for the selected sequence. Nothing to init.";
			Utils::PrintDebugWarning(methodName, oss.str());
			//TODO not sure it should be like this in case of no children https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/13027290/
		}
	}


	void Selector::OnProcess()
	{
		int childrenIndexSize = GetChildren().size() - 1;

		// Init or continue running current child
		if (GetChild(currentChildIndex).GetStatus() == Status::NONE)
		{
			GetChild(currentChildIndex).Init();
			GetChild(currentChildIndex).Process();
		}
		else if (GetChild(currentChildIndex).GetStatus() == Status::SUCCESS)
		{
			status = Status::SUCCESS;
		}
		else if (GetChild(currentChildIndex).GetStatus() == Status::FAILURE)
		{
			// if last child
			if (currentChildIndex == childrenIndexSize)
			{
				status = Status::FAILURE;
			}
			else
			{
				GetChild(++currentChildIndex).Process();
			}
		}
		//the running case is not needed since it will always be taken care by the BTEngine, through currentNode
	}
}
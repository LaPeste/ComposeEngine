#include "Selector.hpp"

namespace BT
{
	Selector::Selector(Node* parent, std::vector<Node> children) :
		currentChildIndex(0), Node(parent, children)
	{}

	Status Selector::Init()
	{
		int childrenSize = GetChildren().size();
		if (childrenSize == 0)
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream oss;
			oss << "There are no children for the selected sequence. Nothing to init.";
			Utils::PrintDebugWarning(methodName, oss.str());
			//TODO not sure it should be like this in case of no children https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/13027290/
			return Status::SUCCESS;
		}

		Status childResult = GetChild(currentChildIndex).Init();
		if (childResult == Status::SUCCESS)
		{
			SetStatus(Status::SUCCESS);
		}
		else if (childResult == Status::RUNNING)
		{
			SetStatus(Status::RUNNING);
		}
		else // failure
		{
			if (childrenSize == 1)
			{
				SetStatus(Status::FAILURE);
			}
			else
			{
				currentChildIndex++;
				SetStatus(Status::RUNNING);
			}
		}
		return GetStatus();
	}


	Status Selector::Process()
	{
		int childrenIndexSize = GetChildren().size() - 1;
		Status childResult;
		Node currChild = GetChild(currentChildIndex);

		// Init or continue running current child
		if (currChild.GetStatus() == Status::NONE)
		{
			childResult = currChild.Init();
		}
		else
		{
			childResult = currChild.Process();
		}


		if (childResult == Status::SUCCESS)
		{
			SetStatus(Status::SUCCESS);
		}
		else if (childResult == Status::RUNNING)
		{
			SetStatus(Status::RUNNING);
		}
		else //failure
		{
			if (currentChildIndex == childrenIndexSize)
			{
				SetStatus(Status::FAILURE);
			}
			else
			{
				currentChildIndex++;
				SetStatus(Status::RUNNING);
			}
		}
		return GetStatus();
	}
}
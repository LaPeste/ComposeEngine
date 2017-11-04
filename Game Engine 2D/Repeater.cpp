#include "Repeater.hpp"

namespace BT
{
	Repeater::Repeater(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		Node(parent, std::move(children), bt)
	{}

	Status Repeater::Init()
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream logText;
		int childrenSize = GetChildren().size();
		if (childrenSize == 0)
		{
			logText << "There are no children for the selected sequence. Nothing to init.";
			Utils::PrintDebugWarning(methodName, logText.str());
			//TODO not sure it should be like this in case of no children https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/13027290/
			return Status::SUCCESS;
		}

		if (childrenSize > 1)
		{
			logText << "This type of node is not supposed to have more than 1 child. It currently has" << childrenSize << ". The additional children won't be repeated. This looks like a mistake";
			Utils::PrintDebugWarning(methodName, logText.str());
		}

		Status childResult = GetChild(0).Init();
		SetStatus(Status::RUNNING);
		return GetStatus();
	}

	Status Repeater::Process()
	{
		if (GetChildren().size() > 1)
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream logText;
			logText << "This type of node is not supposed to have more than 1 child. It currently has" << GetChildren().size() << ". The additional children won't be repeated. This looks like a mistake";
			Utils::PrintDebugWarning(methodName, logText.str());
		}

		Node& curChild = GetChild(0);
		if (curChild.GetStatus() == Status::RUNNING)
		{
			curChild.Process();
		}
		else //success or fail
		{
			curChild.Init();
		}
		return GetStatus();
	}
}
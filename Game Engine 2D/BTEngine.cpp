#include "BTEngine.hpp"
#include "BehaviourTree.hpp"

namespace BT
{
	BTEngine::BTEngine(World& world) : System<BehaviourTree>(world) {}

	void BTEngine::Update(World& world, const unsigned long int entityIndex)
	{
		std::map<unsigned long int, ComponentBase*>& entity = world.EntitiesComponentsMatrix[entityIndex];
		BehaviourTree* bt = static_cast<BehaviourTree*>(entity[BehaviourTree::Id]);

		Node& currNode = bt->GetCurrentNode();

		// if tree has already run, then do nothing. No reason to go any further.
		if ((bt->GetRoot().GetStatus() == Status::SUCCESS) || (bt->GetRoot().GetStatus() == Status::FAILURE))
		{
			return;
		}

		Status nodeResult;
		if (currNode.GetStatus() == Status::NONE)
		{
			nodeResult = currNode.Init();

		}
		else
		{
			nodeResult = currNode.Process();
		}

		if (nodeResult != Status::RUNNING)
		{
			//  if it was the root then there would be no parent to look for
			if (currNode != bt->GetRoot())
			{
				bt->SetCurrentNode(currNode.GetParent());
			}
		}
	}
}
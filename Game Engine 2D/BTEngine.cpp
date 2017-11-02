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
		if (currNode.GetStatus() == Status::SUCCESS)
		{
			return;
		}

		if (currNode.GetStatus() == Status::NONE)
		{
			currNode.Init();
		}
		else
		{
			currNode.Process();
		}
	}
}
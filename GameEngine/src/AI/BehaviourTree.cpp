#include "AI/BehaviourTree.hpp"
#include <algorithm>

namespace BT
{
	//BehaviourTree class
	BehaviourTree::BehaviourTree(World& world, const unsigned long int entityIndex, GameObject& gameObjectAssociated) :
		root(nullptr), currentNode(this->root.get()), gameObjectAssociated(gameObjectAssociated),
		Component(world, entityIndex)
	{}

	BehaviourTree::~BehaviourTree()
	{
	}	

	Context& BehaviourTree::GetContext()
	{
		return context;
	}

	bool BehaviourTree::ContextValueExist(const std::string& search) const
	{
		return !(context.find(search) == context.end());
	}

	void* BehaviourTree::GetContextValue(const std::string& search) const
	{
		if (!ContextValueExist(search))
		{
			std::string methodName = _FUNCTION_NAME_;
			Utils::PrintDebugError(methodName, "Context does not have the field " + search + ". Abort!");
			throw 1;
		}
		return context.at(search);
	}

	void BehaviourTree::SetContextValue(const std::string& key, void* value)
	{
		context.insert(std::make_pair(key, value));
	}

	Node& BehaviourTree::GetRoot() const
	{
		return *root;
	}

	void BehaviourTree::SetRoot(std::unique_ptr<Node> root)
	{
		this->root = std::move(root);
		currentNode = this->root.get();
	}

	Node& BehaviourTree::GetCurrentNode() const
	{
		return *currentNode;
	}

	void BehaviourTree::SetCurrentNode(Node& currNode)
	{
		currentNode = &currNode;
	}

	GameObject& BehaviourTree::GetGameObjectAssociated() const
	{
		return gameObjectAssociated;
	}

	// Node class
	Node::Node(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt) :
		parent(parent), children(std::move(children)), bt(&bt),
		status(Status::NONE)
	{}

	Node::~Node()
	{}

	Node::Node(Node&& other) :
		parent(other.parent), children(std::move(other.children)),
		status(other.status), bt(other.bt)
	{}

	bool Node::operator==(const Node& other)
	{
		if (parent != other.parent) return false;
		if (children != other.children) return false;
		if (bt != other.bt) return false;

		return true;
	}

	bool Node::operator!=(const Node& other)
	{
		return !(*this == other);
	}

	Node& Node::operator=(Node&& other)
	{
		if (&other != this)
		{
			parent = other.parent;
			children = std::move(other.children);
			status = other.status;
			bt = other.bt;
		}
		return *this;
	}

	Status Node::Process()
	{
		bt->SetCurrentNode(*this);
		status = Status::RUNNING;
		OnProcess();
		// if after the real processing SUCCESS, set all children to Status::NONE
		if (status == Status::SUCCESS)
		{
			for (auto& child : GetChildren())
			{
				child->status = Status::NONE;
				child->ResetNode();
			}
		}
		return status;
	}

	void Node::ResetNode() {}

	Node& Node::GetParent() const
	{
		return *parent;
	}

	std::vector<std::unique_ptr<Node>>& Node::GetChildren()
	{
		return children;
	}

	Node& Node::GetChild(int childIndex)
	{
		return *children[childIndex];
	}

	void Node::AddChild(std::unique_ptr<Node> child)
	{
		children.push_back(std::move(child));
	}

	Status Node::GetStatus() const
	{
		return status;
	}

	void Node::SetStatus(Status status)
	{
		this->status = status;
	}
}



/*
 *    THEORY:
 * How to call copy constructor in derived class when the base class doesn't have default constructor?
 * Call the default copy constructor of the base class generated by the compiler.
 */
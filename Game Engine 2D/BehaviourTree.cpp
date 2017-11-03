#include "BehaviourTree.hpp"
#include <algorithm>

namespace BT
{
	//BehaviourTree class
	BehaviourTree::BehaviourTree(World& world, const unsigned long int entityIndex, std::unique_ptr<Node> root, GameObject& gameObjectAssociated) :
		root(std::move(root)), currentNode(this->root.get()), gameObjectAssociated(gameObjectAssociated),
		Component(world, entityIndex)
	{
		if (!this->root)
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream oss;
			oss << "The passed root node pointer was null";
			Utils::PrintDebugError(methodName, oss.str());
			throw 1;
		}
		//set context to root, since it could not have one at the creation moment.
		this->root->SetBehaviourTree(*this);
	}

	BehaviourTree::~BehaviourTree()
	{
	}
	
	//BehaviourTree::BehaviourTree(const BehaviourTree& other, const GameObject& gameObjectAssosicated) :
	//	Component<BehaviourTree>(other), context(),
	//	gameObjectAssociated(const_cast<GameObject&>(gameObjectAssosicated))
	//{
	//	Node* newRoot = new Node(nullptr, other.GetRoot()->GetChildren(), const_cast<Context&>(other.context));
	//	root = newRoot;
	//	currentNode = *newRoot;
	//}
	//

	//BehaviourTree& BehaviourTree::operator=(const BehaviourTree& other)
	//{
	//	// TODO this is pretty questionable. Why would you make a second BT that is "linked" to a gameobject that has already a BT???
	//	gameObjectAssociated = other.gameObjectAssociated;
	//	Node* newRoot = new Node(nullptr, other.GetRoot()->GetChildren(), const_cast<Context&>(other.context));
	//	root = newRoot;
	//	currentNode = *newRoot;
	//}
	

	Context& BehaviourTree::GetContext() const
	{
		return const_cast<Context&>(context);
	}

	bool BehaviourTree::ContextValueExist(const std::string& search) const
	{
		return !(context.find(search) == context.end());
	}

	void* BehaviourTree::GetContextValue(const std::string& search) const
	{
		if (!ContextValueExist(search))
		{
			std::string methodName = _FUNCION_NAME_;
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

	/*void BehaviourTree::SetRoot(Node * const root)
	{
		if (root != nullptr)
		{
			delete root;
		}
		this->root = root;
	}*/

	Node& BehaviourTree::GetCurrentNode() const
	{
		return *currentNode;
	}

	void BehaviourTree::SetCurrentNode(const Node& currNode)
	{
		currentNode = const_cast<Node*>(&currNode);
	}

	GameObject& BehaviourTree::GetGameObjectAssociated() const
	{
		return gameObjectAssociated;
	}

	// Node class
	Node::Node(Node* parent, std::vector<std::unique_ptr<Node>> children, const BehaviourTree& bt) :
		parent(parent), children(std::move(children)), bt(const_cast<BehaviourTree*>(&bt)),
		status(Status::NONE)
	{ }

	Node::Node(Node* parent, std::vector<std::unique_ptr<Node>> children) :
		parent(parent), children(std::move(children)),
		status(Status::NONE)
	{ }

	Node::~Node()
	{

	}

	/*Node::Node(const Node& other) :
		status(Status::NONE)
	{
		std::copy(other.GetChildren().begin(), other.GetChildren().end(), children);
		context
		parent = new Node(nullptr, Context(), const_cast<Context&>(other.context));

	}*/

	Node::Node(Node&& other) :
		parent(other.parent), children(std::move(other.children)),
		status(other.status), bt(other.bt)
	{
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

	Status Node::Init()
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "Init method was not implemented, while you should have!";
		Utils::PrintDebugError(methodName, oss.str());
		throw 2;
	}

	Status Node::Process()
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "Process method was not implemented, while you should have!";
		Utils::PrintDebugError(methodName, oss.str());
		throw 2;
	}

	Node& Node::GetParent() const
	{
		return *parent;
	}

	void Node::SetParent(Node* parent)
	{
		this->parent = parent;
	}

	std::vector<std::unique_ptr<Node>>& Node::GetChildren() const
	{
		return const_cast<std::vector<std::unique_ptr<Node>>&>(children);
	}

	Node& Node::GetChild(int childIndex)
	{
		return *children[childIndex];
	}

	void Node::AddChild(std::unique_ptr<Node> child)
	{
		children.push_back(std::move(child));
	}

	void Node::SetBehaviourTree(const BehaviourTree& bt)
	{
		this->bt = const_cast<BehaviourTree*>(&bt);
	}

	/*void Node::RemoveChild(Node& child)
	{
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}*/

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
#ifndef _BEHAVIOUR_TREE_HPP_
#define _BEHAVIOUR_TREE_HPP_

#include "stdafx.h"
#include "Components/Component.hpp"

class GameObject;

namespace BT
{
	using Context = std::map<std::string, void*>;

	enum class Status
	{
		NONE = 0,
		SUCCESS,
		FAILURE,
		RUNNING
	};


	class BehaviourTree;

	class Node
	{
	public:
		Node(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt);
		virtual ~Node();

		Node(const Node& other) = delete;
		Node& operator=(const Node& other) = delete;
		bool operator==(const Node& other);
		bool operator!=(const Node& other);
		Node(Node&& other);
		Node& operator=(Node&& other);

		virtual void Init() = 0;
		Status Process();
		virtual void OnProcess() = 0;

		/*!  
		 *	This method is called internally on all children of a node, if any, every time the node itself succeeds or fails.
		 *	Useful for example in a sub-tree rooted to a repeater where you don't want to re-instantiate the full node 
		 *	but you may want to simply reuse all the structures created in the Init. So you need to clean the structures up.
		*/
		virtual void ResetNode();

		// Parent can be null, think about tree root
		Node& GetParent() const;
		std::vector<std::unique_ptr<Node>>& GetChildren();
		Node& GetChild(int childIndex);
		void AddChild(std::unique_ptr<Node> child); //maybe useless
		Status GetStatus() const;
		void SetStatus(Status status);

	protected:
		// must be pointer since it could not have a parent. This way it can be null
		Node* parent;
		std::vector<std::unique_ptr<Node>> children;
		Status status;
		// the bt is used mainly to give a standardized interface to BehaviourTree::context
		BehaviourTree* bt;
	};



	class BehaviourTree : public Component<BehaviourTree>
	{
	public:
		BehaviourTree(World& world, const unsigned long int entityIndex, GameObject& gameObjectAssociated);
		~BehaviourTree() override;

		BehaviourTree(const BehaviourTree& other) = delete;
		BehaviourTree& operator=(const BehaviourTree& other) = delete;

		Context& GetContext();
		bool ContextValueExist(const std::string& search) const;
		void* GetContextValue(const std::string& search) const;
		void SetContextValue(const std::string& key, void* value);
		Node& GetRoot() const;
		void SetRoot(std::unique_ptr<Node> root);
		Node& GetCurrentNode() const;
		void SetCurrentNode(Node& currNode);
		GameObject& GetGameObjectAssociated() const;

	private:
		// A context is used to share information across nodes. The content is set to void pointer so that any kind of information can be shared. It's developer's responsibility to know what to cast to.
		Context context;
		// root has to be a pointer because BehaviourTree has to become the owner of root, hence it'll take responsibility to delete it.
		std::unique_ptr<Node> root;
		Node* currentNode;
		// It's the gameobject to which this behaviour tree is associated
		GameObject& gameObjectAssociated;
	};

}


/************* THEORY *********
Virtual destructor are needed when deleting a derived class through a pointer to base class.
If the destructor of the base class is not defined as virtual then undefined behaviours may arise.

One more thing: destructors are always called in the reverse order of the class derivation.
That means derived class destructor will be invoked first & then base class destructor will be called.
*/

#endif //_BEHAVIOUR_TREE_HPP_
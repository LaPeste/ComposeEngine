#ifndef _BEHAVIOUR_TREE_HPP_
#define _BEHAVIOUR_TREE_HPP_

#include "stdafx.h"
#include "Component.hpp"
#include <memory>

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

	class Node
	{
	public:
		//!This constructor is supposed to be used for the root when you don't have a context.
		Node(std::unique_ptr<Node> parent, std::vector<std::unique_ptr<Node>> children);

		//! Usually the context in this constructor is coming from an existing BehaviourTree
		Node(std::unique_ptr<Node> parent, std::vector<std::unique_ptr<Node>> children, const Context& context);
		virtual ~Node();

		/*! 
		 * context won't be copied since there may be pointers and references to object that should not be copied
		 * It won't copy parent since otherwise the whole subtree above such node will be copied. Same goes for children.
		 * Only the current node is copied, setting parent to null.
		 */
		Node(const Node& other) = delete;

		/*!
		* context won't be copied since there may be pointers and references to object that should not be copied
		* It won't copy parent since otherwise the whole subtree above such node will be copied. Same goes for children.
		* Only the current node is copied, setting parent to null.
		*/
		Node& operator=(const Node& other) = delete;

		Node(Node&& other);
		Node& operator=(Node&& other);

		virtual Status Init();
		virtual Status Process();

		// Parent can be null, think about tree root
		Node& GetParent() const;
		void SetParent(std::unique_ptr<Node> parent);
		std::vector<std::unique_ptr<Node>>& GetChildren() const;
		Node& GetChild(int childIndex);
		void AddChild(std::unique_ptr<Node> child); //maybe useless
		void SetContext(const Context& context);

		/*!
		 * It will remove ALL nodes that are identical to child.
		 * Beware, costly operation! O(n) with n number of children.
		 */
		//void RemoveChild(Node& child);
		Status GetStatus() const;
		void SetStatus(Status status);

	protected:
		std::unique_ptr<Node> parent; // must be pointer since it could not have a parent. This way it can be null
		std::vector<std::unique_ptr<Node>> children;
		Status status;
		// context is owned by the behaviour tree, this is just a ref to that of the BT
		Context* context;
		//BehaviourTree* bt;
	};

	class BehaviourTree : public Component<BehaviourTree>
	{
	public:
		BehaviourTree(World& world, const unsigned long int entityIndex, std::unique_ptr<Node> root, GameObject& gameObjectAssociated);
		~BehaviourTree() override;

		//! context won't be copied since there may be pointers and references to object that should not be copied
		BehaviourTree(const BehaviourTree& other) = delete;

		//! context won't be copied since there may be pointers and references to object that should not be copied
		BehaviourTree& operator=(const BehaviourTree& other) = delete;

		Context& GetContext() const;
		void* GetContextValue(const std::string& search) const;
		void SetContextValue(const std::string& key, void* value);
		Node& GetRoot() const;
		//void SetRoot(Node * const root);
		Node& GetCurrentNode() const;
		void SetCurrentNode(const Node& currNode);

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

#endif _BEHAVIOUR_TREE_HPP_
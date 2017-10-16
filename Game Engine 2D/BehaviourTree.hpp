#ifndef _BEHAVIOUR_TREE_HPP_
#define _BEHAVIOUR_TREE_HPP_

#include "stdafx.h"
#include "Component.hpp"
#include <memory>

namespace BT
{
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
		Node(Node* parent, std::vector<Node> children);
		virtual ~Node();

		virtual Status Init();
		virtual Status Process();

		// Parent can be null, think about tree root
		Node* GetParent() const;
		void SetParent(Node* parent);
		std::vector<Node> GetChildren() const;
		Node& GetChild(int childIndex); //maybe useless
		void AddChild(Node& child);
		/*!
		 * It will remove ALL nodes that are identical to child.
		 * Beware, costly operation! O(n) with n number of children.
		 */
		//void RemoveChild(Node& child);
		Status GetStatus() const;
		void SetStatus(Status status);

	private:
		Node* parent; // must be pointer since it could not have a parent. This way it can be null
		std::vector<Node> children;
		Status status;
	};

	class BehaviourTree : public Component<BehaviourTree>
	{
	public:
		BehaviourTree(World& world, const unsigned long int entityIndex, Node* root);
		~BehaviourTree() override;
		BehaviourTree(const BehaviourTree &) = delete;
		BehaviourTree& operator=(const BehaviourTree &) = delete;

		std::shared_ptr<void> GetContextValue(const std::string& search) const;
		void SetContextValue(const std::string& key, std::shared_ptr<void> value);
		Node* GetRoot() const;
		//void SetRoot(Node * const root);
		Node& GetCurrentNode() const;
		void SetCurrentNode(Node& currNode);

	private:
		// A context is used to share information across nodes. The content is set to void pointer so that any kind of information can be shared. It's developer's responsibility to know what to cast to.
		std::map<std::string, std::shared_ptr<void>> context;
		// root has to be a pointer because BehaviourTree has to become the owner of root, hence it'll take responsibility to delete it.
		Node* root;
		Node& currentNode;
	};

}


/************* THEORY *********
Virtual destructor are needed when deleting a derived class throught a poiter to base class.
If the destructor of the base class is not defined as virtual then undefined behaviours may arise.

One more thing: destructors are always called in the reverse order of the class derivation.
That means derived class destructor will be invoked first & then base class destructor will be called.
*/

#endif _BEHAVIOUR_TREE_HPP_
#ifndef _PATROLLING_HPP_
#define _PATROLLING_HPP_

#include "BehaviourTree.hpp"

class Controller;
class Transform;

namespace BT
{
	class Patrolling : public Node
	{
	public:
		Patrolling(Node* parent, std::vector<std::unique_ptr<Node>> children, BehaviourTree& bt);

		void Init() override;
		void OnProcess() override;

	private:
		sf::Vector2f m_originalPosition;
		sf::Vector2f m_finalPosition;
		bool m_turnBack;

		ComponentsMap* m_entity;
		Controller* m_controller;
		Transform* m_transform;
	};
}

#endif
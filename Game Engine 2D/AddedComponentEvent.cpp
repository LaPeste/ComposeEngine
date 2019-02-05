#include "AddedComponentEvent.hpp"

AddedComponentEvent::AddedComponentEvent(GameObject& gameObjectTarget) :
	m_gameObjectTarget(gameObjectTarget)
{

}

const GameObject& AddedComponentEvent::GetGameObjectTarget()
{
	return m_gameObjectTarget;
}
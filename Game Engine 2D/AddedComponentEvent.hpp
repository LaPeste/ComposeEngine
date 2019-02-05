#ifndef _ADDED_COMPONENT_EVENT_HPP_
#define _ADDED_COMPONENT_EVENT_HPP_

#include "stdafx.h"
#include "EventBase.hpp"

class GameObject;

class AddedComponentEvent : public EventBase
{
public:
	AddedComponentEvent(GameObject& m_entityTarget);

	const GameObject& GetGameObjectTarget();

private:
	GameObject& m_gameObjectTarget;

};

#endif // _ADDED_COMPONENT_EVENT_HPP_
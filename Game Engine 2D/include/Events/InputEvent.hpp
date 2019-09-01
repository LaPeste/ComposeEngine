#ifndef _INPUT_EVENT_HPP_
#define _INPUT_EVENT_HPP_

#include "stdafx.h"
#include "Events/Event.hpp"

enum class InputEventType
{
	LEFT_DOWN = 0,
	LEFT_UP,
	RIGHT_DOWN,
	RIGHT_UP,
	JUMP_PRESSED,
	JUMP_START,
	FREE_FALLING_STOP, //raised when not falling anymore from a previous free falling (jump included)
	CROUCH_DOWN,
	CROUCH_UP,
	FREE_FALLING_START //when falling but not for a jump
};

class InputEvent : public Event<InputEvent>
{
public:
	InputEvent(InputEventType message, unsigned long int targetedGameObject);
	InputEventType GetContent() const;
	unsigned long int GetTargetedGameObject() const;

private:
	InputEventType m_event;
	
	// gameObject targeted by this event
	unsigned long int m_targetedGameObject;
};

#endif
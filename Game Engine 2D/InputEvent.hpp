#ifndef _INPUT_EVENT_HPP_
#define _INPUT_EVENT_HPP_

#include "stdafx.h"
#include "EventBase.hpp"

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

class InputEvent : public EventBase
{
public:
	InputEvent(InputEventType message);
	InputEventType GetContent() const;

private:
	InputEventType event;
};

#endif
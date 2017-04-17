#ifndef _INPUT_EVENT_HPP_
#define _INPUT_EVENT_HPP_

#include "stdafx.h"
#include "EventBase.hpp"

class InputEvent : public EventBase
{
public:
	InputEvent(const std::string& message);
	const std::string& GetMessage() const;

private:
	std::string message;
};

#endif
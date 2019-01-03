#ifndef _EVENT_BASE_HPP_
#define _EVENT_BASE_HPP_

#include "stdafx.h"
#include <functional>

class EventBase
{
public:
	using UID = unsigned int;

	EventBase();

	static UID GetId();

private:
	static UID id;
};

#endif
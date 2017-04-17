#ifndef _EVENT_BASE_HPP_
#define _EVENT_BASE_HPP_

#include "stdafx.h"
#include <functional>

class EventBase
{
public:
	typedef unsigned int UID;

	EventBase();

	static unsigned int GetId();

private:
	static UID id;
};


#endif
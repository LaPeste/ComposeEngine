#ifndef _EVENT_BASE_HPP_
#define _EVENT_BASE_HPP_

#include "stdafx.h"
#include <bitset>

constexpr uint32_t eventsLimit{ 1024 };

class EventBase
{
public:
	using UID = std::bitset<eventsLimit>;

	virtual ~EventBase();

	virtual const UID& GetSubEventId() = 0;

protected:
	static uint32_t m_eventTypeCounter;
};

#endif
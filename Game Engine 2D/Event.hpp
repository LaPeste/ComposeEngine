#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "stdafx.h"
#include <functional>

#include "EventBase.hpp"

template<typename T>
class Event : public EventBase
{
public:
	Event();
	static const UID& GetId();
	const UID& GetSubEventId() override;

protected:
	static UID m_id;
};

#include "Event.tpp"

#endif
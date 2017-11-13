#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include "stdafx.h"
#include <list>
#include "EventBase.hpp"

using EventDelegate = std::function<void(EventBase*)>;

class EventManager
{
public:	
	~EventManager();

	static bool AddListener(EventBase::UID eventId, const EventDelegate* eventDelegate);
	static bool RemoveListener(EventBase::UID eventId, const EventDelegate* eventDelegate);
	static void QueueEvent(EventBase* event);
	static void ProcessEvents();

private:
	static std::vector<EventBase*> eventQueue;
	static std::map<EventBase::UID, std::list<const EventDelegate*>> listeners; //std::list because random removal is O(1), if given the iterator (obviously)
};

#endif
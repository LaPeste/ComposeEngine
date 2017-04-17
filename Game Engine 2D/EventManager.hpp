#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include "stdafx.h"
#include <list>
#include "EventBase.hpp"

typedef std::function<void(EventBase*)> EventDelegate;

class EventManager
{
public:	
	~EventManager();

	static bool AddListener(EventBase::UID eventId, const EventDelegate* eventDelegate);
	static bool RemoveListener(EventBase::UID eventId, const EventDelegate* eventDelegate);
	static void QueueEvent(EventBase* event);
	static void ProcessEvents();

private:
	static std::vector<EventBase*> eventQueue; //std::list because random removal is O(1)
	static std::map<EventBase::UID, std::list<const EventDelegate*>> listeners;
};

#endif
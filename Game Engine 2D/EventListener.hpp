#ifndef _EVENT_LISTENER_HPP_
#define _EVENT_LISTENER_HPP_

#include "stdafx.h"
#include "EventBase.hpp"
#include "EventManager.hpp"

class EventListener
{
public:
	~EventListener();

	template<typename EVENT_TYPE>
	bool OnGameEvent(std::function<void(EVENT_TYPE*)> delegateEvent);

protected:
	bool OnGameEvent(EventBase::UID eventId, EventDelegate* delegate);

private:
	std::vector<std::pair<EventBase::UID, EventDelegate*>> registeredEvents;
};

template<typename T>
bool EventListener::OnGameEvent(std::function<void(T*)> delegateEvent)
{
	EventDelegate* function = new EventDelegate([&, delegateEvent](EventBase* event) {  // [&, delegateEvent] (called capture list) means take everything by reference but delegateEvent which is passed by copy. Without that, at the exit of the scope of the method delegateEvent would point to an empty (gone out of scope) input parameter.
		T* castedEvent = static_cast<T*>(event);
		delegateEvent(castedEvent);
	});
	return OnGameEvent(T::GetId(), function);
}

#endif
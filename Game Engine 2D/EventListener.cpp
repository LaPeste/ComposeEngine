#include "EventListener.hpp"

/*
Helper class from which you are supposed to inherit the objects that want to be listener for specific event.
The help comes from the fact that you don't have to take care of removing delegates before destroying subclass of EventListener,
since ~EventListener takes already care of this for you.
*/

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
#if LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
	std::ostringstream oss;
	oss << "dctr called";
	Utils::PrintDebugLog(methodName, oss.str());
#endif

	for(const auto& event : m_registeredEvents)
	{
		EventManager::RemoveListener(event.first, event.second);
	}
}

bool EventListener::OnGameEvent(EventBase::UID eventId, EventDelegate* delegate)
{
	if (delegate == nullptr)
	{
		std::string methodName = _FUNCTION_NAME_;
		std::ostringstream oss;
		oss << "You have tried to add a null delegate for event=" << eventId;
		Utils::PrintDebugError(methodName, oss.str());
		throw 1;
	}

	m_registeredEvents.push_back(std::make_pair(eventId, delegate));
	return EventManager::AddListener(eventId, delegate);
}
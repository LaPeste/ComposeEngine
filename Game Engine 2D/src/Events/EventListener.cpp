#include "Events/EventListener.hpp"

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
		delete event.second;
		EventManager::RemoveListener(event.first, event.second);
	}
}
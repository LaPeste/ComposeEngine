#include "Events/EventManager.hpp"
#include <typeinfo>

#include "Events/Event.hpp"

std::vector<EventBase*> EventManager::m_eventQueue;
std::unordered_map<EventBase::UID, std::list<const EventDelegate*>> EventManager::m_listeners;

EventManager::~EventManager()
{
#if LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
	std::ostringstream oss;
	oss << "dctr called";
	Utils::PrintDebugLog(methodName, oss.str());
#endif

	for(const auto& elem : m_eventQueue)
	{
		delete elem;
	}

	for (const auto& eventDelegateList : m_listeners)
	{
		for (const auto& delegate : eventDelegateList.second)
		{
			delete delegate;
		}
	}
}

bool EventManager::AddListener(EventBase::UID eventId, const EventDelegate* eventDelegate)
{
	if (eventDelegate == nullptr)
	{
		std::string methodName = _FUNCTION_NAME_;
		std::ostringstream oss;
		oss << "You have tried to add a null delegate for event=" << eventId;
		Utils::PrintDebugError(methodName, oss.str());
		throw 1;
	}

	//create list for eventId, if never created before
	if (m_listeners.find(eventId) == m_listeners.end())
	{
		std::list<const EventDelegate*> delegatesList;
		m_listeners.insert(std::make_pair(eventId, delegatesList)); //std::make_pair passes by value, so no worries about delegateList being destroyed at the exit of the method
	}

	std::list<const EventDelegate*> delegateList = m_listeners.at(eventId);

	//avoid to add the same EventDelegate for the same eventId
	/*for (std::list<const EventDelegate*>::iterator it = delegateList.begin(); it != delegateList.end(); ++it)
	{
		const EventDelegate* delegateFunc = *it;
		if (delegateFunc->target<EventDelegate*>() == eventDelegate->target<EventDelegate*>())
		{
			std::string methodName = _FUNCTION_NAME_;
			std::ostringstream oss;
			oss << "You have tried to add the same EventDelegate for the eventId= " << eventId;
			Utils::PrintDebugWarning(methodName, oss.str());
			return false;
		}
	}*/

#if LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
	std::ostringstream oss;
	oss << "EventDelegate for the eventId " << eventId << " added";
	Utils::PrintDebugLog(methodName, oss.str());
#endif

	m_listeners.at(eventId).push_back(eventDelegate);
	return true;
}

bool EventManager::RemoveListener(EventBase::UID eventId, const EventDelegate* eventDelegate)
{
	std::string methodName = _FUNCTION_NAME_;
	std::ostringstream oss;

	if (m_listeners.size() == 0) //I'm not sure why this happens... https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/10940586/
	{
		oss << "You have tried to remove a delegate for the event=" << eventId << " but there is not a single eventId in the listeners map.";
		Utils::PrintDebugError(methodName, oss.str());
		return false;
	}

	if (eventDelegate == nullptr)
	{
		oss << "You have tried to remove a null delegate for event=" << eventId;
		Utils::PrintDebugError(methodName, oss.str());
		throw 1;
	}

	if (m_listeners.find(eventId) == m_listeners.end())
	{
		oss << "You have tried to remove an EventDelegate for the eventId= " << eventId << " which does not exist.";
		Utils::PrintDebugError(methodName, oss.str());
		return false;
	}

	std::list<const EventDelegate*> delegateList = m_listeners.at(eventId);
	for (std::list<const EventDelegate*>::iterator it = delegateList.begin(); it != delegateList.end();)
	{
		auto& delegateFunc = *it;
		if (delegateFunc->target<EventDelegate*>() == eventDelegate->target<EventDelegate*>())
		{
			delete delegateFunc;
			delegateList.erase(it);

#if LOG_OUTPUT_CONSOLE
			std::string methodName = _FUNCTION_NAME_;
			std::ostringstream oss;
			oss << "EventDelegate for the eventId " << eventId << " removed!";
			Utils::PrintDebugError(methodName, oss.str());
#endif
			return true;
		}
		else ++it;
	}
	return false;
}

void EventManager::QueueEvent(EventBase* event)
{
//#if LOG_OUTPUT_CONSOLE
//	std::string methodName = _FUNCION_NAME_;
//	std::ostringstream oss;
//	oss << "Queued event with id " << event->GetId();
//	Utils::PrintDebugLog(methodName, oss.str());
//#endif

	m_eventQueue.push_back(event);
}

void EventManager::ProcessEvents()
{
	auto iterEvent = m_eventQueue.begin();
	while (iterEvent != m_eventQueue.end())
	{
		EventBase::UID& eventId = const_cast<EventBase::UID&>((*iterEvent)->GetSubEventId());

		// check who's listening for this event
		if (m_listeners.find(eventId) == m_listeners.end())
		{
			++iterEvent;
			continue;
		}

		// execute the delegate from the listener of the event
		auto& delegateList = m_listeners.at(eventId);
		for (auto iterDelegate = delegateList.begin(); iterDelegate != delegateList.end(); ++iterDelegate)
		{
			(**iterDelegate)(*iterEvent);
		}
		delete *iterEvent;	//delete memory for used event
		iterEvent = m_eventQueue.erase(iterEvent);
	}
}
#include "EventManager.hpp"
#include <typeinfo>

std::vector<EventBase*> EventManager::eventQueue;
std::map<EventBase::UID, std::list<const EventDelegate*>> EventManager::listeners;

EventManager::~EventManager()
{
#if LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
	std::ostringstream oss;
	oss << "dctr called";
	Utils::PrintDebugLog(methodName, oss.str());
#endif

	for(const auto& elem : eventQueue)
	{
		delete elem;
	}

	for (const auto& eventDelegateList : listeners)
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
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "You have tried to add a null delegate for event=" << eventId;
		Utils::PrintDebugError(methodName, oss.str());
		throw 1;
	}

	//create list for eventId, if never created before
	if (listeners.find(eventId) == listeners.end())
	{
		auto delegatesList = std::list<const EventDelegate*>();
		listeners.insert(std::make_pair(eventId, delegatesList)); //std::make_pair passes by value, so no worries about delegateList being destroyed at the exit of the method
	}

	std::list<const EventDelegate*> delegateList = listeners.at(eventId);

	//avoid to add the same EventDelegate for the same eventId
	for (std::list<const EventDelegate*>::iterator it = delegateList.begin(); it != delegateList.end(); ++it)
	{
		const EventDelegate* delegateFunc = *it;
		if (delegateFunc->target<EventDelegate*>() == eventDelegate->target<EventDelegate*>())
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream oss;
			oss << "You have tried to add the same EventDelegate for the eventId= " << eventId;
			Utils::PrintDebugWarning(methodName, oss.str());
			return false;
		}
	}

#if LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
	std::ostringstream oss;
	oss << "EventDelegate for the eventId " << eventId << " added";
	Utils::PrintDebugLog(methodName, oss.str());
#endif

	listeners.at(eventId).push_back(eventDelegate);
	return true;
}

bool EventManager::RemoveListener(EventBase::UID eventId, const EventDelegate* eventDelegate)
{
	std::string methodName = _FUNCION_NAME_;
	std::ostringstream oss;

	if (listeners.size() == 0) //I'm not sure why this happens... https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/10940586/
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

	if (listeners.find(eventId) == listeners.end())
	{
		oss << "You have tried to remove an EventDelegate for the eventId= " << eventId << " which does not exist.";
		Utils::PrintDebugError(methodName, oss.str());
		return false;
	}

	std::list<const EventDelegate*> delegateList = listeners.at(eventId);
	for (std::list<const EventDelegate*>::iterator it = delegateList.begin(); it != delegateList.end();)
	{
		auto& delegateFunc = *it;
		if (delegateFunc->target<EventDelegate*>() == eventDelegate->target<EventDelegate*>())
		{
			delete delegateFunc;
			delegateList.erase(it);

#if LOG_OUTPUT_CONSOLE
			std::string methodName = _FUNCION_NAME_;
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

	eventQueue.push_back(event);
}

void EventManager::ProcessEvents()
{
	auto iterEvent = eventQueue.begin();
	while (iterEvent != eventQueue.end())
	{
		// check who's listening for this event
		if (listeners.find((*iterEvent)->GetId()) == listeners.end())
		{
			++iterEvent;
			continue;
		}

		// execute the delegate from the listener of the event
		auto& delegateList = listeners.at((*iterEvent)->GetId());
		for (auto iterDelegate = delegateList.begin(); iterDelegate != delegateList.end(); ++iterDelegate)
		{
			(**iterDelegate)(*iterEvent);
		}
		delete *iterEvent;	//delete memory for used event
		iterEvent = eventQueue.erase(iterEvent);
	}
}
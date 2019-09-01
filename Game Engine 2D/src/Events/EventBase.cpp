#include "Events/EventBase.hpp"

uint32_t EventBase::m_eventTypeCounter(0);

EventBase::~EventBase()
{

}

const EventBase::UID EventBase::AssignId()
{
	if (m_eventTypeCounter >= eventsLimit)
	{
		DEBUG_ERROR("Limit of event types reached. If this isn't a mistake, then increase the amount of allowed types.");
		throw 5;
	}
	return 1 << m_eventTypeCounter++;
}
#include "Event.hpp"

template<typename T>
typename Event<T>::UID Event<T>::m_id(0);

template<typename T>
Event<T>::Event()
{
	if (m_id == 0)
	{
		if (m_eventTypeCounter >= eventsLimit)
		{
			DEBUG_ERROR("Limit of event types reached. If this isn't a mistake, then increase the amount of allowed types.");
			return;
		}
		m_id = 1 << m_eventTypeCounter++;
	}
}

template<typename T>
const EventBase::UID& Event<T>::GetId()
{
	return m_id;
}

template<typename T>
const EventBase::UID& Event<T>::GetSubEventId()
{
	return Event<T>::GetId();
}

#include "Events/Event.hpp"

// template<typename T>
// typename Event<T>::UID Event<T>::id(0);

template<typename T>
Event<T>::Event()
{
}

template<typename T>
const EventBase::UID& Event<T>::GetId()
{
	return id;
}

template<typename T>
const EventBase::UID& Event<T>::GetSubEventId()
{
	return Event<T>::GetId();
}


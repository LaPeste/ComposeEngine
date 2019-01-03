#include "EventBase.hpp"

unsigned int EventBase::id = 0;

EventBase::EventBase()
{}

EventBase::UID EventBase::GetId()
{
	if (id == 0)
	{
		static unsigned int eventIds = 0;
		id = ++eventIds;
	}
	return id;
}

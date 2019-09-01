#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "stdafx.h"
#include <functional>

#include "Events/EventBase.hpp"

template<typename T>
class Event : public EventBase
{
public:
	Event();
	static const UID& GetId();
	const UID& GetSubEventId() override;

protected:
	// inline vars are a std:C++17
	inline static const UID id = AssignId();
};

#include "../src/Events/Event.tpp"


/****** THEORY *****
	A variable declared inline has the same semantics as a function declared inline:
	it can be defined, identically, in multiple translation units,
	must be defined in every translation unit in which it is used,
	and the behavior of the program is as if there was exactly one variable.
	MOST IMPORTANTLY:
	You don't have to specify an initializer for an inline variable at the point of declaration.
	Nor is the initializer required to be constexpr itself
*/


#endif
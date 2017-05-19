#include "InputEvent.hpp"

InputEvent::InputEvent(InputEventType message) : event(message)
{

}

InputEventType InputEvent::GetContent() const
{
	return event;
}
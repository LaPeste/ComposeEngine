#include "InputEvent.hpp"

InputEvent::InputEvent(InputEventType message, unsigned long int targetedGameObject) :
	event(message), targetedGameObject(targetedGameObject)
{

}

InputEventType InputEvent::GetContent() const
{
	return event;
}

unsigned long int InputEvent::GetTargetedGameObject() const
{
	return targetedGameObject;
}

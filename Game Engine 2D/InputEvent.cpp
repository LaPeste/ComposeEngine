#include "InputEvent.hpp"

InputEvent::InputEvent(InputEventType message, unsigned long int targetedGameObject) :
	m_event(message), targetedGameObject(targetedGameObject)
{

}

InputEventType InputEvent::GetContent() const
{
	return m_event;
}

unsigned long int InputEvent::GetTargetedGameObject() const
{
	return targetedGameObject;
}

#include "InputEvent.hpp"

InputEvent::InputEvent(const std::string& message) : message(message)
{

}

const std::string& InputEvent::GetMessage() const
{
	return message;
}
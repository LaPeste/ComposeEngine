#include "Event.h"

Event::Event()
{

}
 
Event::~Event()
{

}

void Event::OnEvent(sf::Event& e)
{
	switch (e.type)
	{
		case sf::Event::KeyPressed:
			OnKeyDown(e.key);
			break;
		case sf::Event::KeyReleased:
			OnKeyUp(e.key);
			break;
		case sf::Event::JoystickButtonPressed:
			switch (e.JoystickButtonPressed)
			{
				case sf::Joystick::Axis::X :
					//call go left/right
					break;
				case sf::Joystick::Axis::Y:
					//call crouch when down
					break;
				default:
					break;
			}
			break;
		case sf::Event::Closed:
			OnExit();
			break;
		default:
			break;
	}
}

void Event::OnExit()
{

}

void Event::OnKeyDown(sf::Event::KeyEvent input)
{
	
}

void Event::OnKeyUp(sf::Event::KeyEvent input)
{
	
}

void Event::OnMinimize()
{
	
}

void Event::OnRestore()
{
	
}

void Event::OnResize(int w, int h)
{
	
}

void Event::OnExpose()
{
	
}


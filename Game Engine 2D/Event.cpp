#include "Event.hpp"

Event::Event()
{

}
 
Event::~Event()
{

}

void Event::OnEvent(const sf::Event& e)
{
	switch (e.type)
	{
		case sf::Event::KeyPressed:
			OnKeyDown(e.key);
			break;
		case sf::Event::KeyReleased:
			OnKeyUp(e.key);
			break;
		case sf::Event::JoystickButtonPressed: //this is wrong, it should be arranged like above
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

void Event::OnKeyDown(const sf::Event::KeyEvent& input)
{
	
}

void Event::OnKeyUp(const sf::Event::KeyEvent& input)
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


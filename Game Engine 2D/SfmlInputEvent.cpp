#include "SfmlInputEvent.hpp"
#include "Camera.hpp"

SfmlInputEvent::SfmlInputEvent()
{

}
 
SfmlInputEvent::~SfmlInputEvent()
{

}

void SfmlInputEvent::OnEvent(const sf::Event& e, World& world, const unsigned long entityIndex)
{
	switch (e.type)
	{
		case sf::Event::KeyPressed:
			OnKeyDown(e.key, world, entityIndex);
			break;
		case sf::Event::KeyReleased:
			OnKeyUp(e.key, world, entityIndex);
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

void SfmlInputEvent::OnExit()
{

}

void SfmlInputEvent::OnKeyDown(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex)
{
    
}

void SfmlInputEvent::OnKeyUp(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex)
{
    
}

void SfmlInputEvent::OnMinimize()
{
	
}

void SfmlInputEvent::OnRestore()
{
	
}

void SfmlInputEvent::OnResize(int w, int h)
{
	
}

void SfmlInputEvent::OnExpose()
{
	
}


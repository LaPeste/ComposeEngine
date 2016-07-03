#include "Event.hpp"
#include "Camera.hpp"
#include "GameObjectManager.hpp"

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
    sf::Vector2<float> cameraPos = Camera::GetInstance()->GetPosition();
    sf::Vector2<float> cameraPosNoTarget = Camera::GetInstance()->GetPosition();
    sf::Vector2<float> playerPos = GameObjectManager::GetPlayer()->GetPosition();
    switch (input.code)
    {
        case sf::Keyboard::Key::A:
            GameObjectManager::GetPlayer()->MoveLeft = true;
            //            std::cout << "targetX " << cameraPos.x << " ,  targetY " << cameraPos.y << std::endl;
            //            std::cout << "playerX " << playerPos.x << " ,  playery " << playerPos.y << std::endl;
            if(Camera::GetInstance()->GetCameraMode() == CameraMode::FREE)
            {
                Camera::GetInstance()->SetPosition(cameraPosNoTarget.x - 5.0f, cameraPosNoTarget.y);
            }
            break;
        case sf::Keyboard::Key::D:
            GameObjectManager::GetPlayer()->MoveRight = true;
            //            std::cout << "targetX " << cameraPos.x << " ,  targetY " << cameraPos.y << std::endl;
            //            std::cout << "playerX " << playerPos.x << " ,  playery " << playerPos.y << std::endl;
            if(Camera::GetInstance()->GetCameraMode() == CameraMode::FREE)
            {
                Camera::GetInstance()->SetPosition(cameraPosNoTarget.x + 5.0f, cameraPosNoTarget.y);
            }
            break;
        case sf::Keyboard::Key::S:
            GameObjectManager::GetPlayer()->Crouch = true;
            if(Camera::GetInstance()->GetCameraMode() == CameraMode::FREE)
            {
                Camera::GetInstance()->SetPosition(cameraPosNoTarget.x, cameraPosNoTarget.y + 5.0f);
            }
            break;
        case sf::Keyboard::Key::W:
            GameObjectManager::GetPlayer()->Crouch = true;
            if(Camera::GetInstance()->GetCameraMode() == CameraMode::FREE)
            {
                Camera::GetInstance()->SetPosition(cameraPosNoTarget.x, cameraPosNoTarget.y - 5.0f);
            }
            break;
        case sf::Keyboard::Key::Space:
            GameObjectManager::GetPlayer()->Jump();
            break;
            //Add the cases that you need
        default:
            break;
    }
}

void Event::OnKeyUp(const sf::Event::KeyEvent& input)
{
    switch (input.code)
    {
        case sf::Keyboard::Key::A:
            GameObjectManager::GetPlayer()->MoveLeft = false;
            break;
        case sf::Keyboard::Key::D:
            GameObjectManager::GetPlayer()->MoveRight = false;
            break;
        case sf::Keyboard::Key::S:
            GameObjectManager::GetPlayer()->Crouch = false;
            break;
        case sf::Keyboard::Key::Space:
            //		GameObjectManager::GetPlayer()->CanJump = false;
            break;
            //Add the cases that you need
        default:
            break;
    }
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


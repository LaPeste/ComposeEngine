//
//  Camera.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 04/04/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Camera.hpp"
#include "Engine.hpp"
#include "Components/Transform.hpp"
#include "Entities/EntityManager.hpp"

Camera* Camera::instance;

Camera::Camera(float cameraZoomWidth, float cameraZoomHeight) :
    cameraTargetPos(0.0f, 0.0f),
    cameraFreePos(0.0f, 0.0f),
    mode (CameraMode::FOLLOW_PLAYER),//TODO (Constants::CAMERA_MODE) how to achieve this? I can't get it in the constants
    width(cameraZoomWidth), height(cameraZoomHeight)
{

}

Camera::~Camera()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugLog(methodName, "dctr called");
#endif
}

void Camera::CreateInstance(float cameraZoomWidth, float cameraZoomHeight)
{
    if(instance != nullptr)
    {
		std::string methodName = _FUNCTION_NAME_;
        Utils::PrintDebugError(methodName, "You're trying to instantiate the camera twice!");
        return;
    }
    instance = new Camera(cameraZoomWidth, cameraZoomHeight);
}

Camera * Camera::GetInstance()
{
    if(instance == nullptr)
    {
		std::string methodName = _FUNCTION_NAME_;
        Utils::PrintDebugError(methodName, "Trying to get a camera, but an instance is not created yet!");
        return nullptr;
    }
    return instance;
}

void Camera::Update()
{
    if(mode == CameraMode::FOLLOW_PLAYER && EntityManager::GetPlayerId() != 99999) //99999 is the defaulted value that I am using
    {
        World& world = Engine::GetInstance().CurrentWorld;
		Transform* transform = static_cast<Transform*>(world.EntitiesComponentsMatrix[EntityManager::GetPlayerId()][Transform::Id]);
		if (transform == nullptr)
		{
			std::string methodName = _FUNCTION_NAME_;
			Utils::PrintDebugError(methodName,"player does'not have a Transform component!");
			throw 1;
		}

		sf::Vector2f playerPos { transform->GetPosition() };
        const auto halfWidthCamera { GetWidth() / 2 };
        const auto halfHeightCamera { GetHeight() / 2 };
        const auto halfWidthPlayer { Constants::PLAYER_WIDTH / 2 };
        const auto halfHeightPlayer { Constants::PLAYER_HEIGHT / 2 };

        //if the camera doesn't reach the left or right limit of the map
        if((playerPos.x + halfWidthPlayer > halfWidthCamera) &&
           (playerPos.x + halfWidthPlayer + halfWidthCamera < Engine::GetInstance().GetMapLoader().getMapSize().x))
        {
            cameraTargetPos.x = playerPos.x - halfWidthCamera + halfWidthPlayer;
        }
        
        if((playerPos.y + halfHeightPlayer > halfHeightCamera) &&
           (playerPos.y + halfHeightPlayer + halfHeightCamera < Engine::GetInstance().GetMapLoader().getMapSize().y))
        {
            cameraTargetPos.y = playerPos.y - halfHeightCamera + halfHeightPlayer;
        }
    }
    else
    {
        //...TODO when we introduce a proper free camera mode https://freedcamp.com/Andreas_Projects_FJu/Compose_Engine_MbDa/todos/9988728/
    }
}

void Camera::Draw()
{
    Engine::GetInstance().GetWindow()->setView(
        sf::View {
            sf::FloatRect { Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Constants::CAMERA_ZOOM_WIDTH, Constants::CAMERA_ZOOM_HEIGHT }
        });
}

//******************
// GETTERS AND SETTERS
//******************

const sf::Vector2f & Camera::GetPosition() const
{
    if(mode == CameraMode::FOLLOW_PLAYER) return cameraTargetPos;
    
    else return cameraFreePos;
}


void Camera::SetPosition(float x, float y)
{
    if(mode == CameraMode::FOLLOW_PLAYER)
    {
        cameraTargetPos.x = x - Constants::SCREEN_WIDTH/2;
        cameraTargetPos.y = y - Constants::SCREEN_HEIGHT/2;
    }
    else
    {
        cameraFreePos.x = x;
        cameraFreePos.y = y;
    }
}

const float Camera::GetWidth() const
{
    return width;
}

const float Camera::GetHeight() const
{
    return height;
}

const CameraMode & Camera::GetCameraMode() const
{
    return mode;
}

void Camera::SetCameraMode(CameraMode mode)
{
    Camera::mode = mode;
}

const sf::Vector2f & Camera::GetModePosition(CameraMode whichPositionToSet) const
{
    if(whichPositionToSet == CameraMode::FREE) return cameraFreePos;
    
    else return cameraTargetPos;
}

void Camera::SetModePosition(float x, float y, CameraMode whichPositionToSet)
{
    if(whichPositionToSet == CameraMode::FREE)
    {
        cameraFreePos.x = x;
        cameraFreePos.y = y;
    }
    else
    {
        cameraTargetPos.x = x;
        cameraTargetPos.y = y;
    }
}

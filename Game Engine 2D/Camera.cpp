//
//  Camera.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 04/04/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Camera.h"
#include "GameObjectManager.h"
#include "Engine.h"

using namespace sf;

Camera* Camera::instance;

Camera::Camera() :
    cameraTargetPos(0.0f, 0.0f),
    cameraFreePos(0.0f, 0.0f),
    mode (CameraMode::FOLLOW_PLAYER) //(Constants::CAMERA_MODE) how to achieve this? I can't get it in the constants
{

}

Camera::~Camera()
{
#ifdef LOG_OUTPUT_CONSOLE
    Utils::PrintDebugLog("~Camera()", "dctr called");
#endif
}

void Camera::CreateInstance()
{
    if(instance != nullptr)
    {
        Utils::PrintDebugError("Camera::CreateInstance()", "You're trying to instantiate the camera twice!");
        return;
    }
    instance = new Camera;
}

Camera * Camera::GetInstance()
{
    if(instance == nullptr)
    {
        Utils::PrintDebugError( "Camera::GetInstance", "Trying to get camera, but an instance is not created yet!");
        return nullptr;
    }
    return instance;
}

void Camera::Update()
{
    if(mode == CameraMode::FOLLOW_PLAYER)
    {
        Vector2f playerPos = GameObjectManager::GetPlayer()->GetPosition();
        float newPosX = playerPos.x - Constants::CAMERA_ZOOM_WIDTH/2 + Constants::PLAYER_WIDTH/2;
        float newPosY = playerPos.y - Constants::CAMERA_ZOOM_HEIGHT/2 + Constants::PLAYER_HEIGHT/2;

        //if the camera doesn't reach the left or right limit of the map
        if( ( playerPos.x - Constants::PLAYER_WIDTH/2 > Constants::CAMERA_ZOOM_WIDTH/2 - Constants::PLAYER_WIDTH/2 ) &&
            ( playerPos.x + Constants::PLAYER_WIDTH/2 + Constants::CAMERA_ZOOM_WIDTH/2 < Constants::SCREEN_WIDTH ) )
        {
            cameraTargetPos.x = newPosX;
        }
        
        if( ( playerPos.y - Constants::PLAYER_HEIGHT/2 > Constants::CAMERA_ZOOM_HEIGHT/2 - Constants::PLAYER_HEIGHT/2 ) &&
           ( playerPos.y + Constants::PLAYER_WIDTH/2 + Constants::CAMERA_ZOOM_HEIGHT/2 < Constants::SCREEN_HEIGHT ) )
        {
            cameraTargetPos.y = newPosY;
        }
    }
    else
    {
        //...TODO when we introduce a proper free camera mode
    }
}

void Camera::Draw()
{
    Engine::GetInstance().GetWindow()->setView(
                                sf::View {
                                    sf::FloatRect { Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Constants::CAMERA_ZOOM_WIDTH, Constants::CAMERA_ZOOM_HEIGHT
                                    }
                                } );
}

const Vector2f & Camera::GetPosition() const
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

const CameraMode & Camera::GetCameraMode() const
{
    return mode;
}

void Camera::SetCameraMode(CameraMode mode)
{
    Camera::mode = mode;
}

const Vector2f & Camera::GetModePosition(CameraMode whichPositionToSet) const
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
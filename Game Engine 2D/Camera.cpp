//
//  Camera.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 04/04/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Camera.h"

Camera* Camera::instance(new Camera());

Camera::Camera() :
    posX (0), posY (0),
    targetX (0), targetY (0),
    mode (CameraMode::FOLLOW_PLAYER) //(Constants::CAMERA_MODE) how to achieve this? I can't get it in the constants
{
    if(mode == CameraMode::FOLLOW_PLAYER)
    {
        //SetTargetPos(/*make it point to the player's position which I'm trying to get from a static gameobject manager*/)
    }
}

Camera::~Camera()
{
#ifdef LOG_OUTPUT_CONSOLE
    Utils::PrintDebugLog("~Camera()", "dctr called");
#endif
    //delete instance;
}

void Camera::CreateInstance()
{
    instance = new Camera;
}

Camera* Camera::GetInstance()
{
    if(instance != nullptr)
    {
        return instance;
    }
    else
    {
        Utils::PrintDebugError( "Camera::GetInstance", "Trying to get camera, but an instance is not created yet!");
        return nullptr;
    }
}

const sf::Vector2<int> Camera::GetPos() const
{
    return sf::Vector2<int>(posX, posY);
}

void Camera::SetPos(int x, int y)
{
    posX = x;
    posY = y;
}

void Camera::SetTargetPos(int* const x, int* const y)
{
    targetX = x;
    targetY = y;
}

const CameraMode& Camera::GetCameraMode() const
{
    return mode;
}

void Camera::SetCameraMode(CameraMode mode)
{
    Camera::mode = mode;
}
//
//  Camera.cpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 04/04/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#include "Camera.h"

Camera::Camera() :
    x (0), y (0),
    targetX (0), targetY (0),
    TargetMode (CameraMode::TARGET_MODE_NORMAL)//(Constants::CAMERA_MODE)
{}

void Camera::CreateInstance()
{
    
}
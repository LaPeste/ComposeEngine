//
//  Camera.hpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 04/04/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "stdafx.h"

enum class CameraMode
{
    FREE,
    FOLLOW_PLAYER
};


class Camera 
{
    
public:
    static void CreateInstance(float cameraZoomWidth, float cameraZoonHeight); //singleton lazy initialization
    ~Camera();
    static Camera* GetInstance();
    
    //Delete operators. The following methods could create duplicates of the singleton instance!!
    Camera(Camera const&) = delete; //copy constructor
    void operator=(Camera const&) = delete; //copy assignment operator
    
    void Update();
    void Draw();
    
    void SetCameraMode(CameraMode mode);
    const CameraMode& GetCameraMode() const;
    
    const sf::Vector2f& GetPosition() const;
    void SetPosition(float x, float y);
    const float GetWidth() const;
    const float GetHeight() const;
    const sf::Vector2f& GetModePosition(CameraMode whichPositionToSet) const; // whichPositionToSet decides if to read the free camera pos or the target camera pos
    void SetModePosition(float x, float y, CameraMode whichPositionToSet); // whichPositionToSet decides if to change the free camera pos or the target camera pos
    
private:
    Camera(float cameraZoomWidth, float cameraZoomHeight);
    static Camera* instance;
    
    sf::Vector2f cameraFreePos;
    sf::Vector2f cameraTargetPos;
    float width, height;
    
    CameraMode mode;
};

#endif

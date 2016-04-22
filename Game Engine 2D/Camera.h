//
//  Camera.hpp
//  Game Engine 2D
//
//  Created by Andrea Catalini on 04/04/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "stdafx.h"

enum class CameraMode
{
    FREE,
    FOLLOW_PLAYER
};


class Camera 
{
    
public:
    static void CreateInstance(); //singleton lazy initialization
    ~Camera();
    static Camera* GetInstance();
    
    //delete methods that you don't want. The following methods could create duplicates of the singleton instance!!
    Camera(Camera const&) = delete; //copy constructor
    void operator=(Camera const&) = delete; //copy assignment operator
    
    void SetCameraMode(CameraMode mode);
    const CameraMode& GetCameraMode() const;
    
    const sf::Vector2<int> GetPos() const;
    void SetPos(int x, int y);
    void SetTargetPos(int* const x, int* const y);
    
    
private:
    Camera();
    static Camera* instance;
    
    int posX, posY;
    int* targetX;
    int* targetY;
    
    CameraMode mode;
};

#endif

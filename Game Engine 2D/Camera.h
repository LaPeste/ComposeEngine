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

enum CameraMode
{
    TARGET_MODE_NORMAL,
    TARGET_MODE_CENTRAL
};

class Camera
{
    
public:
    static void CreateInstance();
    ~Camera();
    static const Camera& GetInstance();
    
    //delete methods that you don't want. The following methods could create duplicates of the singleton instance!!
    Camera(Camera const&) = delete; //copy constructor
    void operator=(Camera const&) = delete; //copy assignment operator
    
    CameraMode TargetMode;
    
    const sf::Vector2<int> GetPos() const;
    void SetPos(int x, int y);
    
    
private:
    Camera();
    static Camera instance;
    
    int x, y;
};

#endif

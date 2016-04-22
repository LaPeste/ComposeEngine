#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "stdafx.h"
#include "Camera.h"

//NOTE: Since only the primitive types can be instantiated in the source file, I decided to move all initializations directly in the source file.

class Constants
{
public:
    //************************
    // General game settings
    //************************
    
	static const unsigned int SCREEN_WIDTH;
	static const unsigned int SCREEN_HEIGHT;
	static const unsigned int SCREEN_DEPTH;
	static const float SPEED;
    static const int GAME_FRAMERATE_TARGET;
    static const std::string GAME_NAME;
    
    //************************
    // Camera settings
    //************************
    
    static const float CAMERA_ZOOM_WIDTH;  // I think this is in pixel of the map file (tmx)
    static const float CAMERA_ZOOM_HEIGHT;
    
    //************************
    // Player data
    //************************
    
    //Sprite settings
    static const std::string PLAYER_SPRITE_NAME;
    static const int PLAYER_SPRITE_STARTING_X;
    static const int PLAYER_SPRITE_STARTING_Y;
    static const int PLAYER_WIDTH;
    static const int PLAYER_HEIGHT;
    static const int SPACE_BETWEEN_SPRITE_X;
    static const int SPACE_BETWEEN_SPRITE_Y;
    static const int PLAYER_SPRITE_MAX_FRAME;
    static const int ANIMATION_FRAMERATE;
    static const bool REVERSE_ANIMATION;
    
    //Movement settings
    static const float PLAYER_STEP_SIZE;
    static const int PLAYER_PHYSICAL_STARTING_X;
    static const int PLAYER_PHYSICAL_STARTING_Y;
    
    //************************
    // Map data
    //************************
    
    //static const CameraMode CAMERA_MODE;
};


#endif
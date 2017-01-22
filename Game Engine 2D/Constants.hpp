#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include "stdafx.h"
//#include "Camera.hpp"

//NOTE: Since only the primitive types can be instantiated in the source file, I decided to move all initializations directly in the source file.

class Constants
{
public:
	//************************
	// Technical settings
	//************************
	//static const std::string SIGNATURE_METHOD_LOGS;
    
	static const unsigned int SCREEN_WIDTH;
	static const unsigned int SCREEN_HEIGHT;
	static const unsigned int SCREEN_DEPTH;
    static const int GAME_FRAMERATE_TARGET;
    static const std::string GAME_NAME;
	static const std::string RESOURCE_PATH;
    
    //************************
    // Camera settings
    //************************
    
    static const float CAMERA_ZOOM_WIDTH;  // I think this is in pixel of the map file (tmx)
    static const float CAMERA_ZOOM_HEIGHT;
//    static const CameraMode CAMERA_MODE; // TODO I cannot get this to work! fix it!
    
    //************************
    // Player data
    //************************
    
    static const std::string PLAYER_NAME;
    
    //Sprite settings
    static const std::string PLAYER_SPRITE_PATH;
    static const int PLAYER_SPRITE_STARTING_X;
    static const int PLAYER_SPRITE_STARTING_Y;
    static const int PLAYER_WIDTH;
    static const int PLAYER_HEIGHT;
    static const bool PLAYER_TO_ANIMATE;
    static const int SPACE_BETWEEN_SPRITE_X; //space between every frame in the frames set
    static const int SPACE_BETWEEN_SPRITE_Y;
    static const int PLAYER_SPRITE_MAX_FRAME;
    static const int ANIMATION_FRAMERATE;
    static const bool REVERSE_ANIMATION;
    static const float OFFSET_COL_X;
    static const float OFFSET_COL_Y;
    
    //Movement settings
    static const float PLAYER_MAXSPEED_X, PLAYER_MAXSPEED_Y;
    static const float PLAYER_MAX_ACCELERATION_X, PLAYER_MAX_ACCELERATION_Y;
    static const float PLAYER_STEP_SIZE;
    static const int PLAYER_PHYSICAL_STARTING_X;
    static const int PLAYER_PHYSICAL_STARTING_Y;
    
    //************************
    // In game settings
    //************************
    static const float IN_GAME_GRAVITY;
    
    
    //************************
    // Maps
    //************************
	static const std::string MAP_DIRECTORY;
    static const std::string TEST_MAP;
    
    //static const CameraMode CAMERA_MODE;
    
    //************************
    // Map Layers
    //************************
    static const std::string COLLISION_LAYER;
    static const std::string GROUND_LAYER;
    static const std::string ENTITY_INDEX_PROPERTY;
};


#endif

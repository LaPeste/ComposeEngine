#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "stdafx.h"

//Since only the primitive types can be instantiated in the source file, I decided to move all initializations directly in the source file.

class Constants
{
public:
	static const unsigned int SCREEN_WIDTH;
	static const unsigned int SCREEN_HEIGHT;
	static const unsigned int SCREEN_DEPTH;
	static const float SPEED;
    static const int GAME_FRAMERATE_TARGET;
    static const std::string GAME_NAME;
    
    //************************
    // Player data
    //************************
    
    //Sprite info
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
    
    //************************
    // Map data
    //************************
    

};


#endif
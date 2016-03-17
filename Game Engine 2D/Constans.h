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
    
    
    //************************
    //* Player data
    //************************
    
    //Sprite info
    static const std::string PLAYER_SPRITE_NAME;
    static const unsigned int PLAYER_SPRITE_STARTING_X;
    static const unsigned int PLAYER_SPRITE_STARTING_Y;
    static const unsigned int PLAYER_WIDTH;
    static const unsigned int PLAYER_HEIGHT;
    
	static const unsigned int FRAMERATE_TARGET;

	static const std::string GAME_NAME;


};


#endif
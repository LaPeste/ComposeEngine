#include "Constants.h"

const unsigned int Constants::SCREEN_WIDTH = 1024;
const unsigned int Constants::SCREEN_HEIGHT = 768;
const unsigned int Constants::SCREEN_DEPTH = 32;
const float Constants::SPEED = 3;


//player data
//Sprite variables --> animation assumes that the sprite-set is horizontally developed
const std::string Constants::PLAYER_SPRITE_NAME = "mariosheet.gif";
const int Constants::PLAYER_SPRITE_STARTING_X = 39;
const int Constants::PLAYER_SPRITE_STARTING_Y = 57;
const int Constants::PLAYER_WIDTH = 15;
const int Constants::PLAYER_HEIGHT = 16;
const int Constants::SPACE_BETWEEN_SPRITE_X = 15;
const int Constants::SPACE_BETWEEN_SPRITE_Y = 0;
const int Constants::PLAYER_SPRITE_MAX_FRAME = 4;
const int Constants::ANIMATION_FRAMERATE = 500; //in millisecond
const bool Constants::REVERSE_ANIMATION = true;

const int Constants::GAME_FRAMERATE_TARGET = 32;

const std::string Constants::GAME_NAME = "Mario Clone";
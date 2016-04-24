#include "Constants.h"

//************************
// General game data
//************************

const unsigned int Constants::SCREEN_WIDTH = 1024;
const unsigned int Constants::SCREEN_HEIGHT = 768;
const unsigned int Constants::SCREEN_DEPTH = 32;
const float Constants::SPEED = 3;
const std::string Constants::GAME_NAME = "Mario Clone";
const float Constants::CAMERA_ZOOM_WIDTH = 300;
const float Constants::CAMERA_ZOOM_HEIGHT = 400;

//************************
// Player data
//************************

//Sprite variables --> animation assumes that the sprite-set is horizontally developed
const std::string Constants::PLAYER_SPRITE_NAME = "mariosheet.gif";
const int Constants::PLAYER_SPRITE_STARTING_X = 39;
const int Constants::PLAYER_SPRITE_STARTING_Y = 57;
const int Constants::PLAYER_WIDTH = 15;
const int Constants::PLAYER_HEIGHT = 16;
const int Constants::SPACE_BETWEEN_SPRITE_X = 15;
const int Constants::SPACE_BETWEEN_SPRITE_Y = 0;
const int Constants::PLAYER_SPRITE_MAX_FRAME = 4;
const int Constants::ANIMATION_FRAMERATE = 200; //in millisecond
const bool Constants::REVERSE_ANIMATION = false;
const int Constants::GAME_FRAMERATE_TARGET = 32;

//Movement settings
const float Constants::PLAYER_STEP_SIZE = 3;
const int Constants::PLAYER_PHYSICAL_STARTING_X = 40;
const int Constants::PLAYER_PHYSICAL_STARTING_Y = 50;

//************************
// Map data
//************************

//const CameraMode CAMERA_MODE = CameraMode::TARGET_MODE_NORMAL;


#include "Constants.hpp"

//************************
// General game data
//************************

const unsigned int Constants::SCREEN_WIDTH = 1024;
const unsigned int Constants::SCREEN_HEIGHT = 768;
const unsigned int Constants::SCREEN_DEPTH = 32;
const std::string Constants::GAME_NAME = "Mario Clone";
const float Constants::CAMERA_ZOOM_WIDTH = 300;
const float Constants::CAMERA_ZOOM_HEIGHT = 400;

//************************
// Player data
//************************

const std::string Constants::PLAYER_NAME = "Mario";

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
const float Constants::OFFSET_COL_X = 2;
const float Constants::OFFSET_COL_Y = 2;

//Movement settings
const float Constants::PLAYER_MAXSPEED_X = 4;
const float Constants::PLAYER_MAXSPEED_Y = 6;
const float Constants::PLAYER_STEP_SIZE = 3;
const int Constants::PLAYER_PHYSICAL_STARTING_X = 40;
const int Constants::PLAYER_PHYSICAL_STARTING_Y = 60;

//************************
// In game settings
//************************
const float Constants::IN_GAME_GRAVITY = 0.75f;

//************************
// Map data
//************************
const std::string Constants::COLLISION_LAYER = "Collision Objects";
//const CameraMode CAMERA_MODE = CameraMode::TARGET_MODE_NORMAL;


#include "Constants.hpp"

//************************
// Technical settings
//************************
#ifdef __APPLE__
const std::string Constants::RESOURCE_PATH = resourcePath();
#elif INTERNAL_DEBUG
// const std::string Constants::RESOURCE_PATH = std::string{__FILE__}.append("/resources/");
const std::string Constants::RESOURCE_PATH = "/home/andrea/Development/ComposeEngine/GameEngine/resources/";
#else // in RELEASE
const std::string Constants::RESOURCE_PATH = "resources/";
#endif

//************************
// General game data
//************************
const unsigned int Constants::SCREEN_WIDTH = 1024;
const unsigned int Constants::SCREEN_HEIGHT = 768;
const unsigned int Constants::SCREEN_DEPTH = 32;
const std::string Constants::GAME_NAME = "Mario Clone";
const float Constants::CAMERA_ZOOM_WIDTH = 400;
const float Constants::CAMERA_ZOOM_HEIGHT = 300;
const unsigned int Constants::RENDERING_FPS_TARGET {144};

//************************
// Player data
//************************
const std::string Constants::PLAYER_NAME = "Mario";

//Sprite variables --> animation assumes that the sprite-set is horizontally developed
const std::string Constants::PLAYER_SPRITE_PATH = "characters/Mario.png";

const int Constants::PLAYER_SPRITE_STARTING_X = 48;
const int Constants::PLAYER_SPRITE_STARTING_Y = 10;
const int Constants::PLAYER_WIDTH = 14;
const int Constants::PLAYER_HEIGHT = 20;
const bool Constants::PLAYER_TO_ANIMATE = true;
const int Constants::SPACE_BETWEEN_SPRITE_X = 3;
const int Constants::SPACE_BETWEEN_SPRITE_Y = 0;
const int Constants::PLAYER_SPRITE_MAX_FRAME = 2;
const int Constants::ANIMATION_FRAMERATE = 200; //in millisecond
const bool Constants::REVERSE_ANIMATION = false;
const unsigned int Constants::UPDATE_FPS_TARGET {32};
const float Constants::OFFSET_COL_X = 2; //this should be used for offsetting the bounding box collider on the x axis
const float Constants::OFFSET_COL_Y = 2; //this is the same but for the y axis

//Movement settings
const float Constants::PLAYER_MAXSPEED_X = 4;
const float Constants::PLAYER_MAXSPEED_Y = 10;
const float Constants::PLAYER_MAX_ACCELERATION_X = 0.5f;
const float Constants::PLAYER_MAX_ACCELERATION_Y = 0.5f;
const float Constants::PLAYER_STEP_SIZE = 3;
const int Constants::PLAYER_PHYSICAL_STARTING_X = 40;
const int Constants::PLAYER_PHYSICAL_STARTING_Y = 500;

//************************
// In game settings
//************************
const float Constants::IN_GAME_GRAVITY = 0.75f;

//************************
// Maps
//************************
const std::string  Constants::MAP_DIRECTORY = "maps/";
const std::string  Constants::TEST_MAP = "Test_Level.tmx";

//************************
// Map Layers
//************************
const std::string Constants::COLLISION_LAYER = "Collision Layer";
const std::string Constants::GROUND_LAYER = "Ground Layer";
//const CameraMode CAMERA_MODE = CameraMode::TARGET_MODE_NORMAL;
const std::string Constants::ENTITY_INDEX_PROPERTY = "Entity Index";

#include "stdafx.h"
#include "Player.hpp"
#include "Engine.hpp"
#include "FPS.hpp"
#include "ResourcePath.hpp" // Here is a small helper for you ! Have a look.

inline GameObjectFlags operator|(GameObjectFlags a, GameObjectFlags b)
{return static_cast<GameObjectFlags>(static_cast<int>(a) | static_cast<int>(b));}

inline GameObjectFlags operator&(GameObjectFlags a, GameObjectFlags b)
{return static_cast<GameObjectFlags>(static_cast<int>(a) & static_cast<int>(b));}

Player::Player(bool toAnimate, std::string name) :
    GameObject(toAnimate, Constants::PLAYER_SPRITE_MAX_FRAME, Constants::ANIMATION_FRAMERATE, Constants::REVERSE_ANIMATION,
               Constants::PLAYER_PHYSICAL_STARTING_X, Constants::PLAYER_PHYSICAL_STARTING_Y,
                Constants::PLAYER_MAXSPEED_X, Constants::PLAYER_MAXSPEED_Y,
               0.5f, 0.5f,
               Constants::OFFSET_COL_X, Constants::OFFSET_COL_Y,
               (GameObjectFlags::GRAVITY),
               name,
               GameObjectType::UserPlayer)
{
    
#ifdef _WIN32
    std::string loadPath = "images/" + Constants::PLAYER_SPRITE_NAME;
#elif __APPLE__ && __MACH__
    std::string loadPath = resourcePath() + Constants::PLAYER_SPRITE_NAME;
//#should do the linux version
#endif
    
    GameObject::Load(loadPath, Constants::PLAYER_SPRITE_STARTING_X, Constants::PLAYER_SPRITE_STARTING_Y, Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
    assert(IsLoaded()); //you do this because you can't return a value from a constructor!!
    SetPosition(60.0f, (float)Constants::SCREEN_HEIGHT/2);
}

Player::~Player()
{
#ifdef LOG_OUTPUT_CONSOLE
    Utils::PrintDebugLog("~Player()", "dctr called");
#endif
}

/*** THEORY ****

If the argument expression of this macro with functional form compares equal to zero (i.e., the expression is false),
 message is written to the standard error device and abort is called, terminating the program execution.

 */
#ifndef _GAME_OBJECT_HPP_
#define _GAME_OBJECT_HPP_

#include "stdafx.h"
#include "Event.hpp"
#include "Animator.hpp"
#include <tmx/MapObject.h>
#include "GameObjectType.hpp"

//TODO arrange all the methods to support the fact that now a gameObject can contain a mapObject, hence a draw for example, if it's a mapObject, may not be necessary

class GameObject
{
public:
    /////////////////
    // Summary:
    // Constructor thought for gameobjects that can perform actions
    ////////////////
    GameObject(bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation,
                        float startingPosX, float startingPosY,
                        float maxSpeedX, float maxSpeedY,
                        float customAccelerationX, float customAccelerationY,
                        float offsetColX, float offsetColY,
                        GameObjectFlags flags,
                        std::string name,
                        const GameObjectType& type);
    /////////////////
    // Summary:
    // Constructor thought for map gameobject that can animate, as they come from tmx maps
    ////////////////
    GameObject(tmx::MapObject* mapObject,
               bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation,
               float offsetColX, float offsetColY,
               GameObjectFlags flags);
    
    /////////////////
    // Summary:
    // Constructor thought for map gameobject, as they come from tmx maps
    ////////////////
    GameObject(tmx::MapObject* mapObject,
               float offsetColX, float offsetColY,
               GameObjectFlags flags);
    
	virtual ~GameObject();

	virtual void Load(const std::string& filename);
	virtual void Load(const std::string & filename, int startingLeft, int startingTop, int width, int height);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update();
	virtual const sf::Vector2f GetPosition() const;
	virtual void SetPosition(float x, float y);
    virtual void SetPosition(sf::Vector2f position);
    
    /////////////////
    // Summary:
    // Returns mapObject*, nullptr is mapObject* doesn't point to anything.
    ////////////////
    tmx::MapObject* GetMapObject() const;
    const GameObjectType& GetGameObjectType() const;
    long GetID() const;
    void SetID(const long id);
    std::string GetName() const;
    virtual void Cleanup();
	virtual bool IsLoaded() const;
    bool IsMapObject() const;
    virtual bool OnCollision(GameObject* otherEntity);
    sf::Sprite GetSprite() const;
//    virtual bool Collides(sf::Sprite sprite);
    virtual bool Collides();//float originX, float originY, float width, float height);
    
    bool MoveLeft;
    bool MoveRight;
    bool Crouch;
    bool Jump;
    void MoveTo(float x, float y);
    const bool IsDead() const;
    void SetDeath(bool dead);
    
    GameObjectFlags Flags;

protected:
	float timeSinceLastDrawnFrame; //in seconds
    bool toAnimate;
    Animator animator;
    
    float accelerationX, accelerationY; //++left , --right
    float customAccelerationX, customAccelerationY;
    float speedX, speedY; //instantaneous velocity
    float maxSpeedX, maxSpeedY;
    
    void UpdatePosition();
    void StopMove();
    void Animate();
    bool PosValid(float x, float y);
    sf::Vector2f collisionPoints[4]; //holds the 4 corners of the boundaries of the sprite
    
    bool dead;

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string filename;
    tmx::MapObject* mapObject; //to use only when it's not a scripted GameObject, but comes from a tmx map
    GameObjectType gameObjectType;
	bool isLoaded;
    bool isMapOObject; //to set when it's a tmx::MapObject to which collision matter
    const float offsetColX, offsetColY; //used to offset the size of the entity in order to adjust where a collision is actually going to be raised
    long id; //needed for identification in the list of objects
    std::string name; //GameObject's name
    
    void SetSubTexture(int startingLeft, int startingTop, int width, int height);
    
};

#endif


/*
THEORY: explicit constructor TODO...

*/
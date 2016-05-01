#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "stdafx.h"
#include "Event.h"
#include "Animator.h"

class GameObject
{

public:
	explicit GameObject(bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation, float startingPosX, float startingPosY);
	virtual ~GameObject();

	virtual void Load(const std::string& filename);
	virtual void Load(const std::string& filename, int startingLeft, int startingTop, int width, int height);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update();
	virtual const sf::Vector2f GetPosition() const;
	virtual void SetPosition(float x, float y);
	virtual void Cleanup();
	virtual bool IsLoaded() const;
    sf::Sprite GetSprite() const;

protected:
	
	float timeSinceLastDrawnFrame; //in seconds
    bool toAnimate;
    Animator animator;

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string filename;
	bool isLoaded;
    
    void SetSubTexture(int startingLeft, int startingTop, int width, int height);

};

#endif


/*
THEORY: explicit constructor TODO...

*/
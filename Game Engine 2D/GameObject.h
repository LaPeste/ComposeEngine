#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "stdafx.h"
#include "Event.h"
#include "Animator.h"

class GameObject : public Event
{

public:
	explicit GameObject(bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation);
	virtual ~GameObject();

	virtual void Load(std::string filename);
	virtual void Load(std::string filename, int startingLeft, int startingTop, int width, int height);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Update();
	virtual sf::Vector2f GetPosition() const;
	virtual void SetPosition(float x, float y);
	virtual void Cleanup();
	virtual bool IsLoaded() const;

protected:
	sf::Sprite& GetSprite();
	float timeSinceLastDrawnFrame; //in seconds
    bool toAnimate;

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string filename;
    Animator animator;
	bool isLoaded;
    
    void SetSubTexture(int startingLeft, int startingTop, int width, int height);

};

#endif
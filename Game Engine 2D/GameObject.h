#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "stdafx.h"
#include "Event.h"

class GameObject : public Event
{

public:
	GameObject();
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

private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::string filename;
	bool isLoaded;

};

#endif
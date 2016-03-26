#include "GameObject.h"
#include "Engine.h"

GameObject::GameObject(bool toAnimate, int spriteMaxFrame, int animationFrameRate, bool reverseAnimation) :
    isLoaded (false),
    toAnimate(false),
    animator(spriteMaxFrame, animationFrameRate, reverseAnimation)
{
    GameObject::toAnimate = toAnimate;
}

GameObject::~GameObject()
{

}

void GameObject::Load(std::string filename)
{
	if (texture.loadFromFile(filename) == false)
	{
		filename = "";
		isLoaded = false;
	}
	else
	{
		GameObject::filename = filename;
		sprite.setTexture(texture);
		isLoaded = true;
	}
}

///Loads only a part of the texture
void GameObject::Load(std::string filename, int startingLeft, int startingTop, int width, int height)
{
	if (texture.loadFromFile(filename) == false)
	{
		filename = "";
		isLoaded = false;
	}
	else
	{
		GameObject::filename = filename;
        sprite.setTexture(texture);
//		sf::Rect<int> subTextureRect(startingLeft, startingTop, width, height);
//		sprite.setTextureRect(subTextureRect);
        SetSubTexture(startingLeft, startingTop, width, height);
        if(sprite.getTexture() != nullptr)
        {
            isLoaded = true;
#ifdef DEBUG
            Utils::PrintDebug("GameObject::Load(...)", "texture correctly loaded!");
#endif
        }
        else
        {
            isLoaded = false;
#ifdef DEBUG
            Utils::PrintDebug("GameObject::Load(...)", "texture not correctly loaded!");
#endif

        }
    }
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (isLoaded)
	{
        if(toAnimate)
        {
            sprite.setTextureRect(animator.Animate());
        }
        window.draw(sprite);
//		sf::Time actualTime = Engine::GetInstance().Clock().getElapsedTime();
//		timeSinceLastDrawnFrame = actualTime.asSeconds();
	}
}

void GameObject::SetSubTexture(int startingLeft, int startingTop, int width, int height)
{
    sf::Rect<int> subTextureRect(startingLeft, startingTop, width, height);
    sprite.setTextureRect(subTextureRect);
}

void GameObject::Update()
{

}

void GameObject::Cleanup()
{

}

bool GameObject::IsLoaded() const
{
	if (isLoaded) return true;

	return false;
}


//*************
//Getters and Setters
//*************

sf::Sprite& GameObject::GetSprite()
{
	return sprite;
}


sf::Vector2f GameObject::GetPosition() const
{
    if (isLoaded)
    {
        return sprite.getPosition();
    }
    return sf::Vector2f();
}

void GameObject::SetPosition(float x, float y)
{
    if (isLoaded)
    {
        sprite.setPosition(x, y);
    }
}

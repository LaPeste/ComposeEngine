#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "GameObject.h"

class Player : public GameObject
{
public:
    using GameObject::GameObject;
    Player(bool toAnimate);
	~Player();

	void Update();
	void Draw(sf::RenderWindow& rw);
	float GetVelocity();
	bool MoveLeft;
	bool MoveRight;
	bool Crouch;
	bool Jump;
	void OnMove(float xMove, float yMove);

	//plus all the method needed for the engine, based on your needs
protected:
	void OnKeyDown(sf::Event::KeyEvent input);

private:
	float velocity; //--left ++right
	const float speed; //instantaneous velocity
	const float maxVelocity;
	//void GoLeft();
	//void GoRight();
	//void Jump();
	//void Crouch();
};

//*** THEORY ***
// Using the keyword public in the class we are only deriving the public members of GameObject.
// In this way Mario has no direct access to private members. This is a good way of hiding complexity from derived classes, as well as keeping control where it should properly be.
// When you are declaring a class you can declare members as public, protected and private, you use the same three keywords when deriving a class from a base class. 

#endif
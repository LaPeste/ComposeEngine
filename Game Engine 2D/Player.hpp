#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "GameObject.hpp"

class Player : public GameObject
{
public:
//    using GameObject::GameObject;
    Player(bool toAnimate, std::string name);
	~Player();

//	void Update() override;
//	void Draw(sf::RenderWindow & rw) override;
//	float GetVelocity() const;

	//plus all the method needed for the engine, based on your needs
protected:
//	void OnKeyDown(const sf::Event::KeyEvent& input);

private:
	
};

/*** THEORY ***
 This public keyword after the colon (:) denotes the most accessible level the members inherited from the class that follows it (in this case Polygon) will have from the derived class (in this case Rectangle). Since public is the most accessible level, by specifying this keyword the derived class will inherit all the members with the same levels they had in the base class.
 
 With protected, all public members of the base class are inherited as protected in the derived class. Conversely, if the most restricting access level is specified (private), all the base class members are inherited as private.
*/

#endif
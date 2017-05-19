//
//  Controller.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 18/09/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "stdafx.h"
#include "Component.hpp"

class Controller : public Component<Controller>
{
public:
    Controller(World& world, const unsigned long int entityIndex);
	~Controller();
    
	bool GetMoveRight() const;
	bool GetMoveLeft() const;
	bool GetCrouch() const;
	bool GetCanJump() const;
	bool IsJumping() const;

	void SetMoveRight(bool moveRight);
	void SetMoveLeft(bool moveLight);
	void SetCrouch(bool crouch);
	void SetCanJump(bool canJump);

	//ATTENTION: You should never ever use this method, unless you really know what you are doing!!!!
	void SetIfJumping(bool jumping);

	bool Jump(World& world, const unsigned long entityIndex);

private:
    bool moveRight;
    bool moveLeft;
    bool crouch;
    bool canJump; //used to check conditions like: touching the ground etc etc
	bool currentlyInTheAir;

};

#endif /* _CONTROLLER_HPP_ */

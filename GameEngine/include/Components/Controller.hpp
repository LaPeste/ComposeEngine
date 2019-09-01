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
#include "Components/Component.hpp"

class Controller : public Component<Controller>
{
public:
    Controller(World& world, const unsigned long int entityIndex);
	~Controller() override;
    
	bool GetMoveRight() const;
	bool GetMoveLeft() const;
	bool GetCrouch() const;
	bool CanJump() const;
	bool IsJumping() const;
	bool IsFreeFalling() const;
	bool WantToJump() const;

	void SetMoveRight(bool moveRight);
	void SetMoveLeft(bool moveLight);
	void SetCrouch(bool crouch);
	void SetJumping(bool jumping);
	void SetWantToJump(bool wantToJump);

	//ATTENTION: You should never ever use this method, unless you really know what you are doing!!!!
	void SetFreeFalling(bool freeFalling);

private:
    bool moveRight;
    bool moveLeft;
    bool crouch;
    //bool canJump; //used to check conditions like: touching the ground etc etc
	bool wantToJump;
	bool jumping;
	bool freeFalling;

};

#endif /* _CONTROLLER_HPP_ */

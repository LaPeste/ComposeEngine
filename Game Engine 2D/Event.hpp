#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include "stdafx.h"
#include "World.hpp"

/*
  Protected methods are't made pure virtual simply not to force the implementer to implement not needed methods.
  It's more a shortcut than anything else.
*/
class Event
{
public:
	Event();
	virtual ~Event();
	virtual void OnEvent(const sf::Event& e, World& world, const unsigned long entityIndex);

protected:
	virtual void OnKeyDown(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex);
	virtual void OnKeyUp(const sf::Event::KeyEvent& input, World& world, const unsigned long entityIndex);

	virtual void OnMinimize();
	virtual void OnRestore();
	virtual void OnResize(int w, int h);
	virtual void OnExpose();
	virtual void OnExit();

private:

};

#endif
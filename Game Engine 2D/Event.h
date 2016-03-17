#ifndef _EVENT_H_
#define _EVENT_H_

#include "stdafx.h"

class Event
{
public:
	Event();
	virtual ~Event();
	virtual void OnEvent(sf::Event& e);

protected:
	virtual void OnKeyDown(sf::Event::KeyEvent input);
	virtual void OnKeyUp(sf::Event::KeyEvent input);

	virtual void OnMinimize();
	virtual void OnRestore();
	virtual void OnResize(int w, int h);
	virtual void OnExpose();
	virtual void OnExit();

private:

};

#endif
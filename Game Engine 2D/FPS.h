#ifndef _FPS_H_
#define _FPS_H_

#include "stdafx.h"

class FPS
{
public:
	FPS();
	~FPS();

	static unsigned int GetFPS();
	static float GetSpeedFactor();
	static void Update();

private:
	static int frameRate;
	static int frames;
	static double speedFactor;
	static int lastTime;
	static sf::Clock clock;
};
#endif
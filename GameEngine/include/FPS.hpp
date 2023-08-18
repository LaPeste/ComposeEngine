#ifndef _FPS_HPP_
#define _FPS_HPP_

#include "stdafx.h"

//#define FRAME_RATE

class FPS
{
public:
	FPS();
	~FPS();

	static unsigned int GetUpdateFPS();
	static unsigned int GetRenderFPS();
	static float GetSpeedFactor();
	static void Update();
	static bool ShouldEngineUpdate();
	static bool ShouldEngineRender();


private:

	static unsigned int updateFrameRate;
	static float updateFrameTime; // in ms
	static bool shouldEngineUpdate;
	static unsigned int tempUpdateFrames;
	static float updateFrameTimeCounter;

	static unsigned int renderFrameRate;
	static float renderFrameTime; // in ms
	static bool shouldEngineRender;
	static unsigned int tempRenderFrames;
	static float renderFrameTimeCounter;
	
	static double speedFactor;
	static int lastFrameTime;
	static sf::Clock clock;
};
#endif
#include "FPS.hpp"

int FPS::frameRate(0);
int FPS::lastTime(0);
double FPS::speedFactor(0);
int FPS::frames(0);
sf::Clock FPS::clock;

FPS::FPS() {}

FPS::~FPS() {}

unsigned int FPS::GetFPS()
{
	return frameRate;
}

float FPS::GetSpeedFactor()
{
	return speedFactor;
}

void FPS::Update()
{
	if (clock.getElapsedTime().asMilliseconds() < 1000)
	{
		frames++;
		double timeFrame = clock.getElapsedTime().asMilliseconds() - lastTime;
		speedFactor = timeFrame / 1000 * Constants::FPS_TARGET;
		lastTime = clock.getElapsedTime().asMilliseconds();
	}
	else
	{
		clock.restart();
		frameRate = frames;
		frames = 0;
		lastTime = 0;

#ifdef FRAME_RATE
		DEBUG_LOG("FPS --> " + std::to_string(frameRate) + "\n");
#endif
	}
}
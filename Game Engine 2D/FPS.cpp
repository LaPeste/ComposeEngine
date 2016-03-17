#include "FPS.h"
#include "Constans.h"

unsigned int FPS::frameRate(0);
unsigned int FPS::lastTime(0);
float FPS::speedFactor(0);
unsigned int FPS::frames(0);
sf::Clock FPS::clock;

FPS::FPS() {}

FPS::~FPS() {}

const unsigned int FPS::GetFPS()
{
	return frameRate;
}

const float FPS::GetSpeedFactor()
{
	return speedFactor;
}

void FPS::Update()
{
	if (clock.getElapsedTime().asMilliseconds() < 1000)
	{
		frames++;
		unsigned int timeFrame = clock.getElapsedTime().asMilliseconds() - lastTime;
		speedFactor = timeFrame / 1000 * Constants::FRAMERATE_TARGET;
		lastTime = clock.getElapsedTime().asMilliseconds();
	}
	else
	{
		clock.restart();
		frameRate = frames;
		frames = 0;
		lastTime = 0;
	}
}
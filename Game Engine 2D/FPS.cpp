#include "FPS.h"

int FPS::frameRate(0);
int FPS::lastTime(0);
float FPS::speedFactor(0);
int FPS::frames(0);
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
		int timeFrame = clock.getElapsedTime().asMilliseconds() - lastTime;
		speedFactor = timeFrame / 1000 * Constants::GAME_FRAMERATE_TARGET;
		lastTime = clock.getElapsedTime().asMilliseconds();
	}
	else
	{
		clock.restart();
		frameRate = frames;
		frames = 0;
		lastTime = 0;
#ifdef FRAME_RATE
        std::cout << "FPS --> " << frameRate << "\n";
#endif
	}
}
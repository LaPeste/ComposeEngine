#include "FPS.hpp"

unsigned int FPS::updateFrameRate {0};
float FPS::updateFrameTime {1000.f / Constants::UPDATE_FPS_TARGET};
bool FPS::shouldEngineUpdate {false};
unsigned int FPS::tempUpdateFrames {0};
float FPS::updateFrameTimeCounter {0};

unsigned int FPS::renderFrameRate {0};
float FPS::renderFrameTime {1000.f / Constants::RENDERING_FPS_TARGET};
bool FPS::shouldEngineRender {false};
unsigned int FPS::tempRenderFrames {0};
float FPS::renderFrameTimeCounter {0};

int FPS::lastFrameTime {0};
double FPS::speedFactor {updateFrameTime};

sf::Clock FPS::clock {};

FPS::FPS() {}

FPS::~FPS() {}

unsigned int FPS::GetUpdateFPS()
{
	return updateFrameRate;
}

unsigned int FPS::GetRenderFPS()
{
	return renderFrameRate;
}

float FPS::GetSpeedFactor()
{
	return speedFactor;
}

bool FPS::ShouldEngineUpdate()
{
	return shouldEngineUpdate;
}

bool FPS::ShouldEngineRender()
{
	return shouldEngineRender;
}

void FPS::Update()
{
	auto elapsedMs = clock.getElapsedTime().asMilliseconds();
	if (elapsedMs < 1000)
	{
		auto timeFrame = clock.getElapsedTime().asMilliseconds() - lastFrameTime;
		updateFrameTimeCounter += timeFrame;
		renderFrameTimeCounter += timeFrame;

		if (updateFrameTimeCounter >= updateFrameTime)
		{
			speedFactor = updateFrameTimeCounter / 1000 * Constants::UPDATE_FPS_TARGET;
			++tempUpdateFrames;
			shouldEngineUpdate = true;
			updateFrameTimeCounter = 0.f;
		}
		else
		{
			shouldEngineUpdate = false;
		}
		
		if (renderFrameTimeCounter >= renderFrameTime)
		{
			++tempRenderFrames;
			shouldEngineRender = true;
			renderFrameTimeCounter = 0.f;
		}
		else
		{
			shouldEngineRender = false;
		}
		lastFrameTime = clock.getElapsedTime().asMilliseconds();
	}
	else
	{
		clock.restart();
		updateFrameRate = tempUpdateFrames;
		renderFrameRate = tempRenderFrames;
		tempRenderFrames = 0;
		tempUpdateFrames = 0;
		lastFrameTime = 0;

#ifdef FRAME_RATE
		DEBUG_LOG("Render FPS --> " + std::to_string(renderFrameRate) + "\n");
#endif
	}
}
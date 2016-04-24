#include "stdafx.h"
#include "Engine.h"

int main(int argc, char* argv[])
{

	sf::RenderWindow window;
	Engine& e = Engine::GetInstance();
	e.Launch(&window);
#ifdef LOG_OUTPUT_CONSOLE
    Utils::PrintDebugLog("main()", "terminated");
#endif
	return 0;
}
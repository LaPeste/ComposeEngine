#include "stdafx.h"
#include "Engine.hpp"

int main(int argc, char* argv[])
{

	sf::RenderWindow window;
	Engine& e = Engine::GetInstance();
	e.Launch(&window);
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
    Utils::PrintDebugLog(methodName, "terminated");
#endif
	return 0;
}
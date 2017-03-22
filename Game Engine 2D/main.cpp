#include "stdafx.h"
#include "Engine.hpp"
#include <sstream>
//#include <vld.h>

int main(int argc, char* argv[])
{
	//try to catch exceptions in order to allow stack unwinding
	try
	{
		sf::RenderWindow window;
		Engine& e = Engine::GetInstance();
		e.Launch(&window);
#ifdef LOG_OUTPUT_CONSOLE
		std::string methodName = _FUNCION_NAME_;
		Utils::PrintDebugLog(methodName, "terminated");
#endif
	}
	catch (const int& e) {
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "exception" << e << " was raised";
		Utils::PrintDebugError(methodName, oss.str());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
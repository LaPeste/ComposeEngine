#include "stdafx.h"
#include "Engine.hpp"

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
	catch (const int& e)
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "exception" << e << " was raised. The program is being termianted!";
		Utils::PrintDebugError(methodName, oss.str());
		return EXIT_FAILURE;
	}
	catch (std::bad_alloc)
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "it was not possible to instantiate a new object. The program is being termianted!";
		Utils::PrintDebugError(methodName, oss.str());
		return EXIT_FAILURE;
	}
	catch (std::out_of_range)
	{
		std::string methodName = _FUNCION_NAME_;
		std::ostringstream oss;
		oss << "Silly man, you were trying to access something out of the memory range of your container! You have crashed the application, well done!";
		Utils::PrintDebugError(methodName, oss.str());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
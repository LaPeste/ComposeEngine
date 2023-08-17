#include "stdafx.h"
#include "Engine.hpp"
#include "EngineConfig.h"

//#include <vld.h>

int main(int argc, char* argv[])
{
	std::ostringstream oss;
	oss << "Engine version " << ENGINE_VERSION_MAJOR << "." << ENGINE_VERSION_MINOR;
	Utils::PrintDebugLog(_FUNCTION_NAME_, oss.str());

	//try to catch exceptions in order to allow stack unwinding
	try
	{
		sf::RenderWindow window;
		Engine& e = Engine::GetInstance();
		e.Launch(&window);
#ifdef LOG_OUTPUT_CONSOLE
		std::string methodName = _FUNCTION_NAME_;
		Utils::PrintDebugLog(methodName, "terminated");
#endif
	}
	catch (std::bad_alloc)
	{
		std::ostringstream oss;
		oss << "it was not possible to instantiate a new object. The program is being termianted!";
		Utils::PrintDebugError(_FUNCTION_NAME_, oss.str());
		return EXIT_FAILURE;
	}
	catch (std::out_of_range)
	{
		std::ostringstream oss;
		oss << "Silly man, you were trying to access something out of the memory range of your container! You have crashed the application, well done!";
		Utils::PrintDebugError(_FUNCTION_NAME_, oss.str());
		return EXIT_FAILURE;
	}
	catch (const int& e)
	{
		std::ostringstream oss;
		oss << "exception" << e << " was raised. The program is being termianted!";
		Utils::PrintDebugError(_FUNCTION_NAME_, oss.str());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
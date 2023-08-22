#include "stdafx.h"
#include "Engine.hpp"
#include "EngineConfig.h"

//#include <vld.h>

int main(int argc, char* argv[])
{
	std::ostringstream oss;
	oss << "Engine version " << ENGINE_VERSION_MAJOR << "." << ENGINE_VERSION_MINOR;
	DEBUG_LOG(oss.str());

	//try to catch exceptions in order to allow stack unwinding
	try
	{
		sf::RenderWindow window;
		Engine& e = Engine::GetInstance();
		e.Launch(&window);
	}
	catch (std::bad_alloc)
	{
		DEBUG_ERROR("it was not possible to instantiate a new object. The program is being termianted!");
		return EXIT_FAILURE;
	}
	catch (std::out_of_range)
	{
		DEBUG_ERROR("Silly man, you were trying to access something out of the memory range of your container! You have crashed the application, well done!");
		return EXIT_FAILURE;
	}
	catch (const int& e)
	{
		std::ostringstream oss;
		oss << "exception" << e << " was raised. The program is being termianted!";
		DEBUG_ERROR(oss.str());
		return EXIT_FAILURE;
	}
#ifndef INTERNAL_DEBUG
	catch (...)
	{
		DEBUG_ERROR("An exception of undetermined type was raised");
		return EXIT_FAILURE;
	}
#endif

	return EXIT_SUCCESS;
}
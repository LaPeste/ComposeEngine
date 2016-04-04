#include "stdafx.h"
#include "Engine.h"

int main(int argc, char* argv[])
{

	sf::RenderWindow window;
	Engine& e = Engine::GetInstance();
	e.Launch(&window);
	return 0;
}
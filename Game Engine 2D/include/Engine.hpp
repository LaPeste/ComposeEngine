#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#define LOG_OUTPUT_ALL //all log for tmx

#include "stdafx.h"
#include "Events/Event.hpp"
#include "tmx/MapLoader.hpp"
#include "World.hpp"

class Engine
{

public:
	~Engine();
	static Engine& GetInstance()
	{
		return instance;
	}

	//Delete operators. The following methods could create duplicates of the singleton instance!!
	Engine(Engine const&) = delete; //copy constructor
	void operator=(Engine const&) = delete; //copy assignment operator

	void Launch(sf::RenderWindow* createdWindow); //Starts the engine

	//Utils
	sf::RenderWindow* GetWindow() const;
    tmx::MapLoader& GetMapLoader();

    static World CurrentWorld; //TODO this will become a vector of worlds to support any level of granularity you like
	void Exit();

private:
	static Engine instance; // lazy initialization can't be done because I need a reference to World on application loading for the ClassRegistry.
	Engine();
	enum GameState
	{
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};
    
	//variables
	sf::RenderWindow* mainWindow; //SFML Render Window
	GameState gameState;
    
    tmx::MapLoader ml;

	//methods
	bool Init(); //Initializes the engine
	void MainLoop(); //Main Game Loop
	void ProcessInput(); //Processes user input
	void Update(); //Updates all Engine internals
    void RenderFrame(); //Renders one frame
    void Terminate();
	bool IsExiting();
};

#endif

/* THEORY:
The "const" at the end of a method implies that a call of such method from another object can't in any way modify member variables of the object that owns
the method.


*/

#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#define LOG_OUTPUT_ALL //all log for tmx

#include "stdafx.h"
#include "Event.hpp"
#include "tmx/MapLoader.hpp"
#include "World.hpp"

class Engine : public Event
{

public:
	~Engine();
	static Engine& GetInstance()
	{
		static Engine instance;// Guaranteed to be destroyed.
                               // Instantiated on first use.
		return instance;
	}

	//delete methods that you don't want. The following methods could create duplicates of the singleton instance!!
	Engine(Engine const&) = delete; //copy constructor
	void operator=(Engine const&) = delete; //copy assignment operator

	void Launch(sf::RenderWindow* createdWindow); //Starts the engine
//	void OnKeyDown(const sf::Event::KeyEvent& input) override;
//	void OnKeyUp(const sf::Event::KeyEvent& input) override;

	//Utils
	sf::RenderWindow* GetWindow() const;
    tmx::MapLoader& GetMapLoader();
    
    World World; //TODO maybe getter and setter?

private:
	Engine();
	enum GameState
	{
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};
    
	//variables
	sf::RenderWindow* mainWindow; //SFML Render Window
	GameState gameState;
//	GameObjectManager gameObjectManager;
    
    tmx::MapLoader ml;
	//tmx::Logger logger;

	//methods
	bool Init(); //Initializes the engine
	void MainLoop(); //Main Game Loop
	void ProcessInput(); //Processes user input
	void Update(); //Updates all Engine internals
    void RenderFrame(); //Renders one frame
	void OnExit() override; //from events
    void Terminate();
	bool IsExiting();
};

#endif

/* THEORY:
The "const" at the end of a method implies that a call of such method from another object can't in any way modify member variables of the object that owns
the method.


*/

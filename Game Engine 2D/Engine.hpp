#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include "stdafx.h"
#include "GameObjectManager.hpp"
#include "Event.hpp"
#include <tmx/MapLoader.h>

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
	void OnKeyDown(const sf::Event::KeyEvent& input) override;
	void OnKeyUp(const sf::Event::KeyEvent& input) override;

	//Utils
	sf::RenderWindow* GetWindow() const;
    tmx::MapLoader & GetMapLoader();

private:
	Engine();
	enum GameState
	{
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};
    
    float testPosX, testPosY;

	//variables
	sf::RenderWindow* mainWindow; //SFML Render Window
	GameState gameState;
//	GameObjectManager gameObjectManager;
    
    tmx::MapLoader ml;

	//methods
	bool Init(); //Initializes the engine
	void MainLoop(); //Main Game Loop
	void RenderFrame(); //Renders one frame
	void ProcessInput(); //Processes user input
	void Update(); //Updates all Engine internals
	void OnExit() override;
	bool IsExiting();
};

#endif

/* THEORY:
The "const" at the end of a method implies that a call of such method from another object can't in any way modify member variables of the object that owns
the method.


*/
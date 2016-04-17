#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "stdafx.h"
#include "GameObjectManager.h"
#include "Event.h"
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
//	const sf::Clock& Clock() const; //TODO I'd like to make this function constant so that no one sets the clock

	//Utils
	const sf::RenderWindow* GetWindow() const;

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
	GameObjectManager gameObjectManager;
//	sf::Clock clock;
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
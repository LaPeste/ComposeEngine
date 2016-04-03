#include "Engine.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "FPS.h"

Engine::~Engine(){}

Engine::Engine() : ml(resourcePath())
{
    
}

void Engine::Launch(sf::RenderWindow* createdWindow)
{
	if (gameState != Uninitialized)
		return;

	mainWindow = createdWindow;

	if(!Init())
		throw "Could not initialize Engine";

	while (!IsExiting())
	{
		MainLoop();
	}
}

sf::RenderWindow* Engine::Window() const
{
	return mainWindow;
}

sf::Clock const& Engine::Clock()
{
	return clock;
}

bool Engine::Init()
{
	mainWindow->create(sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::SCREEN_DEPTH), Constants::GAME_NAME);
	gameState = Playing;
	clock;
	if (!mainWindow->isOpen())
		return false;

	//init gameobject manager and its objects
	Player* player = new Player(true);
	gameObjectManager.Add(GameObjectManager::GameObjectType::player, player);
    
    ml.Load("desert.tmx");
	return true;

}

void Engine::MainLoop()
{
	switch (gameState)
	{
		case  Playing:
			{
				ProcessInput();
				Update();
				RenderFrame();
				break;
			}
	}
}

void Engine::RenderFrame()
{
	mainWindow->clear();
    mainWindow->draw(ml); //draw map
    gameObjectManager.DrawAll(*mainWindow);
	mainWindow->display();
}

void Engine::ProcessInput()
{
	sf::Event event;
	while (mainWindow->pollEvent(event))
	{
		OnEvent(event);
	}
}

void Engine::Update()
{
	FPS::Update();
}

bool Engine::IsExiting()
{
	if (gameState != Exiting)
		return false;

	return true;
}

void Engine::OnKeyDown(sf::Event::KeyEvent input)
{
	switch (input.code)
	{
	case sf::Keyboard::Key::A:
		gameObjectManager.GetPlayer()->MoveLeft = true;
		break;
	case sf::Keyboard::Key::D:
		gameObjectManager.GetPlayer()->MoveRight = true;
		break;
	case sf::Keyboard::Key::S:
		gameObjectManager.GetPlayer()->Crouch = true;
		break;
	case sf::Keyboard::Key::Space:
		gameObjectManager.GetPlayer()->Jump = true;
		break;
		//Add the cases that you need
	default:
		break;
	}
}

void Engine::OnKeyUp(sf::Event::KeyEvent input)
{
	switch (input.code)
	{
	case sf::Keyboard::Key::A:
		gameObjectManager.GetPlayer()->MoveLeft = false;
		break;
	case sf::Keyboard::Key::D:
		gameObjectManager.GetPlayer()->MoveRight = false;
		break;
	case sf::Keyboard::Key::S:
		gameObjectManager.GetPlayer()->Crouch = false;
		break;
	case sf::Keyboard::Key::Space:
		gameObjectManager.GetPlayer()->Jump = false;
		break;
		//Add the cases that you need
	default:
		break;
	}
}

void Engine::OnExit()
{
	mainWindow->close();
	//maybe here you hava to call all the needed destructor
	gameState = GameState::Exiting;
}

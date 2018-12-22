#include "Engine.hpp"
#include "Player.hpp"
#include "FPS.hpp"
#include "Camera.hpp"
#include "tmx/Log.hpp"
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"

#include "Movement.hpp"
#include "Renderer.hpp"
#include "Animator.hpp"
#include "InputSystem.hpp"

#include "Controller.hpp"
#include "Velocity.hpp"
#include "Acceleration.hpp"
#include "EntityFlag.hpp"
#include "Appearance.hpp"
#include "BTEngine.hpp"

World Engine::World;
Engine Engine::instance;

Engine::~Engine()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
    Utils::PrintDebugLog(methodName, "dctr called");
#endif
    delete(Camera::GetInstance());
}

Engine::Engine() : ml(Constants::RESOURCE_PATH + Constants::MAP_DIRECTORY) { }

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
    Terminate();
}

sf::RenderWindow* Engine::GetWindow() const
{
	return mainWindow;
}

bool Engine::Init()
{
	mainWindow->create(sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, Constants::SCREEN_DEPTH), Constants::GAME_NAME);
	gameState = Playing;
    
	if (!mainWindow->isOpen())
		return false;
    
    ml.load(Constants::TEST_MAP);
    
    SystemManager::Init(World);
    
    EntityManager::Init(World);
    
    SystemManager::AddSystem(World, new Movement(World));
    SystemManager::AddSystem(World, new Renderer(World));
    SystemManager::AddSystem(World, new Animator(World));
	SystemManager::AddSystem(World, new InputSystem(World));
	SystemManager::AddSystem(World, new BT::BTEngine(World));
    
    Camera::CreateInstance(Constants::CAMERA_ZOOM_WIDTH ,Constants::CAMERA_ZOOM_HEIGHT);

	SystemManager::StartAll(World);

    return true;

}

void Engine::MainLoop()
{
	switch (gameState)
	{
		case GameState::Playing:
		{
			ProcessInput();
			Update();
			RenderFrame();
			break;
		}
		default:
		{
			std::string methodName = _FUNCION_NAME_;
			std::ostringstream oss;
			oss << "GameState= " << gameState << " not recognized";
			Utils::PrintDebugLog(methodName, oss.str());
			break;
		}
	}
}

void Engine::ProcessInput()
{
    sf::Event event;
    while (mainWindow->pollEvent(event))
    {
        SystemManager::ProcessAllInput(World, event);
    }
}

void Engine::Update()
{
    FPS::Update();
    Camera::GetInstance()->Update();
	EventManager::ProcessEvents();
    SystemManager::UpdateAll(World);
	SystemManager::LateUpdateAll(World);
}

void Engine::RenderFrame()
{
	mainWindow->clear();
    mainWindow->draw(ml); //draw map loaded in mapLoader
    Camera::GetInstance()->Draw(); //draw only the camera view
    SystemManager::RenderAll(World); //draw all entities

	mainWindow->display();
}

bool Engine::IsExiting()
{
	if (gameState != Exiting)
		return false;

	return true;
}

void Engine::Exit()
{
    gameState = GameState::Exiting;
}

void Engine::Terminate()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCION_NAME_;
    Utils::PrintDebugLog(methodName, "terminating the engine and taking care of freeing the allocated memory");
#endif
    SystemManager::ExitAll(World);
    mainWindow->close();
}

//*****************
//Getter and Setter
//*****************
tmx::MapLoader & Engine::GetMapLoader()
{
    return ml;
}







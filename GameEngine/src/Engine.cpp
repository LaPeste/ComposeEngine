#include "Engine.hpp"
#include "GameObjects/Player.hpp"
#include "FPS.hpp"
#include "Camera.hpp"
#include "tmx/Log.hpp"
#include "Systems/SystemManager.hpp"
#include "Entities/EntityManager.hpp"
#include "Events/EventManager.hpp"

#include "Systems/Movement.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/Animator.hpp"
#include "Systems/InputSystem.hpp"

#include "Components/Controller.hpp"
#include "Components/Velocity.hpp"
#include "Components/Acceleration.hpp"
#include "Components/EntityFlag.hpp"
#include "Components/Appearance.hpp"
#include "Systems/BTEngine.hpp"
#include "Systems/CollisionDetector.hpp"
#include "GameExample/Behaviours/Systems/FOVspotter.hpp"

World Engine::CurrentWorld;
Engine Engine::instance;

Engine::~Engine()
{
#ifdef LOG_OUTPUT_CONSOLE
	std::string methodName = _FUNCTION_NAME_;
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
    
    SystemManager::Init(CurrentWorld);
    
    EntityManager::Init(CurrentWorld);
    
    SystemManager::AddSystem(CurrentWorld, new Movement(CurrentWorld));
    SystemManager::AddSystem(CurrentWorld, new Renderer(CurrentWorld));
    SystemManager::AddSystem(CurrentWorld, new Animator(CurrentWorld));
	SystemManager::AddSystem(CurrentWorld, new InputSystem(CurrentWorld));
	SystemManager::AddSystem(CurrentWorld, new CollisionDetector(CurrentWorld));
	SystemManager::AddSystem(CurrentWorld, new BT::BTEngine(CurrentWorld));
	SystemManager::AddSystem(CurrentWorld, new FOVspotter(CurrentWorld));
    
    Camera::CreateInstance(Constants::CAMERA_ZOOM_WIDTH ,Constants::CAMERA_ZOOM_HEIGHT);

	SystemManager::StartAll(CurrentWorld);

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
			std::string methodName = _FUNCTION_NAME_;
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
        SystemManager::ProcessAllInput(CurrentWorld, event);
    }
}

void Engine::Update()
{
    FPS::Update();
	if (!FPS::ShouldEngineUpdate())
	{
		return; 
	}
		
	Camera::GetInstance()->Update();
	EventManager::ProcessEvents();
	SystemManager::UpdateAll(CurrentWorld);
	SystemManager::LateUpdateAll(CurrentWorld);
}

void Engine::RenderFrame()
{
	if (!FPS::ShouldEngineRender())
	{ 
		return;
	}

	mainWindow->clear();
    mainWindow->draw(ml); //draw map loaded in mapLoader
    Camera::GetInstance()->Draw(); //draw only the camera view
    SystemManager::RenderAll(CurrentWorld); //draw all entities
	GeometryDebugger::DrawAllShapes();
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
	std::string methodName = _FUNCTION_NAME_;
    Utils::PrintDebugLog(methodName, "terminating the engine and taking care of freeing the allocated memory");
#endif
    SystemManager::ExitAll(CurrentWorld);
    mainWindow->close();
}

//*****************
//Getter and Setter
//*****************
tmx::MapLoader & Engine::GetMapLoader()
{
    return ml;
}







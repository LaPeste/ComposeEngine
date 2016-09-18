#include "Engine.hpp"
#include "GameObjectManager.hpp"
#include "Player.hpp"
#include "FPS.hpp"
#include "Camera.hpp"
#include <tmx/Log.h>
#include "SystemManager.hpp"


Engine::~Engine()
{
#ifdef LOG_OUTPUT_CONSOLE
    Utils::PrintDebugLog("~Engine()", "dctr called");
#endif
    delete Camera::GetInstance();
}

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
//    world; // trying to initialize the object world, not sure though
    
	if (!mainWindow->isOpen())
		return false;
    
    tmx::Logger::SetLogLevel(tmx::Logger::Warning | tmx::Logger::Error);
    ml.Load(Constants::TEST_MAP);
    
    //init gameobject manager and its objects
//    GameObjectManager::Init();
//    Player* player = new Player();
//    GameObjectManager::Add(player);
    
    SystemManager::Init();
    
    Player();
    Camera::CreateInstance(Constants::CAMERA_ZOOM_WIDTH ,Constants::CAMERA_ZOOM_HEIGHT);
    return true;

}

void Engine::MainLoop()
{
	switch (gameState)
	{
		case GameState::Playing:
            ProcessInput();
            Update();
            RenderFrame();
            break;
	}
}

void Engine::ProcessInput()
{
    sf::Event event;
    while (mainWindow->pollEvent(event))
    {
        OnEvent(event, World, 0);
        SystemManager::ProcessAllInput(event);
    }
}

void Engine::Update()
{
//    sf::FloatRect rootNode(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y, Camera::GetInstance()->GetWidth(), Camera::GetInstance()->GetHeight());
//    ml.UpdateQuadTree(rootNode); //update quadtree's rootnode to what's visible in the screen
    FPS::Update();
    Camera::GetInstance()->Update();
//    GameObjectManager::UpdateAll();
    SystemManager::UpdateAll();
}

void Engine::RenderFrame()
{
	mainWindow->clear();
    mainWindow->draw(ml); //draw map loaded in mapLoader
    Camera::GetInstance()->Draw(); //draw only the camera view
//    GameObjectManager::DrawAll(*mainWindow);
    SystemManager::RenderAll(); //draw all entities
	mainWindow->display();
}



bool Engine::IsExiting()
{
	if (gameState != Exiting)
		return false;

	return true;
}

void Engine::OnExit()
{
    gameState = GameState::Exiting;
}

void Engine::Terminate()
{
#ifdef LOG_OUTPUT_CONSOLE
    Utils::PrintDebugLog("Engine::Terminate", "terminating the engine and taking care of freeing the allocated memory");
#endif
    SystemManager::ExitAll();
    mainWindow->close();
}

//*****************
//Getter and Setter
//*****************
tmx::MapLoader & Engine::GetMapLoader() //this doesn't fucking work!!! I hate when it doesn't work >:(
{
    return ml;
}







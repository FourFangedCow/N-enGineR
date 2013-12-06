#include "Precompiled.h"
#include "EngineManager.h"
#include "GameWindow.h"
#include "Console.h"
#include "Graphics.h"
#include "Factory.h"
#include "GameLogic.h"

using namespace Engine;

const char windowTitle[] = "TEST";
const int clientWidth = 1440;
const int clientHeight = 900;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Create the manager
	EngineManager* engine = new EngineManager();

	//Create the needed system
	GameWindow* window = new GameWindow(windowTitle, clientWidth, clientHeight);

	//Adding systems
	engine->AddSystem(new Graphics(WINDOW->hWnd));
	engine->AddSystem(new GameObjectFactory());
	engine->AddSystem(new DebugConsole());
	engine->AddSystem(new GameLogic);
	engine->AddSystem(window);			//Game Window
//	engine->AddSystem(new Sound());		//Sound

	//Initialize all systems
	engine->Initialize();

	//Activate the window
	window->ActivateWindow();

	//Engine update loop
	engine->UpdateEngine();

	//Destroy all engine systems;
	engine->DestroyEngine();

	delete engine;

	return 0;
}

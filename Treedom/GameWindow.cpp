/*
 *	FILE:		GameWindow.cpp
 *	CREATOR:	
 *	PURPOSE:	Makes the game window.
 */

#include "Precompiled.h"
#include "GameWindow.h"
#include "EngineManager.h"

namespace Engine
{
	const char windowsClassName[] = "EngineGameWindowClass";
	GameWindow* WINDOW;


	//Basic message handler; replace with system input
	LRESULT WINAPI MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if(wParam == SC_CLOSE)//0xF060)
		{
			PostQuitMessage(0);
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	GameWindow::GameWindow(const char* windowTitle, int width, int height)
	{
		WINDOW = this;
		ScreenSize = Vec2D((float)width, (float)height);
		RECT fullWinRect = {0, 0, width, height};
		AdjustWindowRect(&fullWinRect, WS_OVERLAPPEDWINDOW, FALSE);

		WNDCLASSEX wc = {sizeof(WNDCLASSEX),	//The size of this structure (passing the size allows Microsoft to update their interfaces and maintain backward compatibility)
			CS_CLASSDC,							//The style of the window class--this is the base type (one device context for all windows in the process)
			MessageHandler,						//The name of the message handling function
			0L, 0L,								//The amount of extra memory to allocate for this class and window
			GetModuleHandle(NULL),				//Handle to the instance that has the windows procedure--NULL means use this file.
			NULL,								//Add an Icon as a resource and add them here
			LoadCursor(NULL, IDC_ARROW),		//Use the default arrow cursor
			NULL, NULL,							//The background brush and menu--these can be NULL
			windowsClassName, NULL};			//The class name and the small icon (NULL just uses the default)

        RegisterClassEx(&wc);

		hInstance = wc.hInstance;

		hWnd = CreateWindow(windowsClassName,	//The class name
			windowTitle,						//The name for the title bar
			WS_OVERLAPPEDWINDOW,				//The style of the window (WS_BORDER, WS_MINIMIZEBOX, WS_MAXIMIZE, etc.)
			CW_USEDEFAULT, CW_USEDEFAULT,		//The x and y position of the window (screen coords for base windows, relative coords for child windows)
			fullWinRect.right-fullWinRect.left,	//Width of the window, including borders
			fullWinRect.bottom-fullWinRect.top,	//Height of the window, including borders and caption
			GetDesktopWindow(),					//The parent window
			NULL,								//The menu for the window
			hInstance,							//The handle to the instance of the window (ignored in NT/2K/XP)
			NULL);	

		if(hWnd == NULL)
		{
			MessageBox(NULL, (LPCSTR)"Window Creation Failed!", (LPCSTR)"Error!", MB_ICONEXCLAMATION | MB_OK);
		}
		
		//Create the input manager
	}

	GameWindow::~GameWindow()
	{
		UnregisterClass(windowsClassName, hInstance);
	}

	//Message checking
	void GameWindow::Update(float dt)
	{
		MSG msg;
		while(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				MessageQuit Quit;
				MANAGER->BroadcastMessage(&Quit);
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void GameWindow::ActivateWindow()
	{
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);
	}
}
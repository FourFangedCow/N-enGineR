/*
 *	FILE:		GameWindow.h
 *	CREATOR:	
 *	PURPOSE:	Header for the window maker thing.
 */

#pragma once

#include "Engine.h"

namespace Engine
{
	class GameWindow : public System
	{
	public:
		GameWindow(const char* windowTitle, int width, int height);
		~GameWindow();

		void ActivateWindow();
		virtual void Update(float dt);
		virtual std::string GetName() {return "GameWindow";}

		HWND hWnd;
		HINSTANCE hInstance;
		POINTS MousePosition;
		Vec2D ScreenSize;
	};

	extern GameWindow* WINDOW;
}
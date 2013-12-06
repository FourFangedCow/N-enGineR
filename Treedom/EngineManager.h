/*
 *	FILE:		EngineManager.h
 *	CREATOR:	Craig Jong
 *	PURPOSE:	Manages all the core elements of the engine.
 */

#pragma once

#include "System.h"

namespace Engine
{
	class EngineManager
	{
	public:
		//Constructor and destructor
		EngineManager();
		~EngineManager();
	
		//Updates all engine components
		void UpdateEngine();
	
		//Destroy all engine components
		void DestroyEngine();
	
		//Sends a message to all systems (like exit, etc)
		void BroadcastMessage(Message* m);
	
		//Add a new system to the manager
		void AddSystem(System* system);
	
		//Initializes systems
		void Initialize();
	
	private:
		//Vector to track all systems
		std::vector<System*> SystemList;
	
		//Last time the game was updated
		unsigned int LastTime;
	
		//Is the game running?
		bool GameActive; 
	};

	class MessageQuit : public Message
	{
	public:
		MessageQuit() : Message(Mid::Quit) {};
	};
	//Pointer to the manager
	extern EngineManager* MANAGER;
}
/*
 *	FILE:		EngineManager.c
 *	CREATOR:	Craig Jong
 *	PURPOSE:	Manages all the core elements of the engine.
 */

#include "Precompiled.h"
#include "EngineManager.h"

namespace Engine
{
	//Declare extern pointer
	EngineManager* MANAGER;

	//Constructor
	EngineManager::EngineManager()
	{
		LastTime = 0;		//Start time
		GameActive = true;	//Set game to active
		MANAGER = this;		//Set manager pointer to new instance
	}
	//Destructor
	EngineManager::~EngineManager()
	{
		//Empty
	}
	//Initialize all engine systems
	void EngineManager::Initialize()
	{
		for(unsigned int i = 0; i < SystemList.size(); ++i)
		{
			SystemList[i]->Initialize();
		}
	}

	void EngineManager::UpdateEngine()
	{
		//Set last time to the current time
		static float timer;
		LastTime = timeGetTime();

		while(GameActive)
		{
			
			unsigned int currenttime = timeGetTime();
			float dt = (currenttime - LastTime) / 1000.0f;
			LastTime = currenttime;
			timer += dt;
			//Loop to update all systems
			for(unsigned int i = 0; i< SystemList.size(); ++i)
			{
				SystemList[i]->Update(dt);
				
			}
		}
		timer = 0;
	}
	
	void EngineManager::BroadcastMessage(Message* message)
	{
		if(message->MessageId == Mid::Quit)
			GameActive = false;

		//Send the message to all systems
		for(unsigned int i = 0; i < SystemList.size(); ++i)
		{
			SystemList[i]->RecieveMessage(message);
		}
	}

	void EngineManager::AddSystem(System* system)
	{
		//Adds a system to the system list
		SystemList.push_back(system);
	}

	void EngineManager::DestroyEngine()
	{
		for(unsigned int i = 0; i < SystemList.size(); i++)
		{
			delete SystemList[SystemList.size() - i - 1];
		}
	}
}
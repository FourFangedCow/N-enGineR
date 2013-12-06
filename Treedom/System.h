/*
 *	FILE:		System.h
 *	CREATOR:	Craig Jong
 *	PURPOSE:	Defines all basic framework
 */


#pragma once

#include "Message.h"

namespace Engine
{
	class System
	{
	public:
		//For sending messages to the manager
		virtual void RecieveMessage(Message* message) {};

		//Updating the engine system
		virtual void Update(float dt) = 0;

		//Provides system name
		virtual std::string GetName() = 0;

		//Initialize the system
		virtual void Initialize(){};

		//Virtaul destructor
		virtual ~System(){};
	};
}
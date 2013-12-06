/*
 *	FILE:		Message.h
 *	CREATOR:	Craig Jong
 *	PURPOSE:	How to 
 */


#pragma once

namespace Engine
{
	namespace Mid
	{
		enum MessageId
		{
			None,
			Quit,
		};
	}

	class Message
	{
	public:
		Message(Mid::MessageId id) : MessageId(id){};
		Mid::MessageId MessageId;
		virtual ~Message(){};
	};
}
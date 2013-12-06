#pragma once

#include "Message.h"
#include "Serialization.h"
#include "ComponentIds.h"

//THE BASE CLASS FOR COMPONENTS
namespace Engine
{
	class GameObjectComposition;
	typedef GameObjectComposition GOC;

	class GameComponent
	{
	public:
		friend class GameObjectComposition;

		virtual void Initialize(){};
		virtual void SendMessage(Message*){};
		virtual void Serialize(Serializer &str){};

		GOC* GetOwner(){return Base;}

		ComponentId TypeId;

	protected:
		virtual ~GameComponent(){};

	private:
		GOC* Base;
	};
}
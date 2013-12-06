

#pragma once

#include "Message.h"
#include "Serialization.h"
#include "Component.h"

namespace Engine
{
	//Typedef for the IDs
	typedef unsigned int GOCId;
	//Typedef for vector
	typedef std::vector<GameComponent*> ComponentArray;

	class GameObjectComposition
	{
	public:
		friend class GameObjectFactory;

		void SendMessage(Message* message);
		
		GameComponent* GetComponent(ComponentId typeId);
		template<typename type> type* GetComponentType(ComponentId typeId);

		void Initialize();

		void Destroy();

		void AddComponent(ComponentId typeId, GameComponent* component);

		GOCId GetId() {return ObjectId;}

	private:
		ComponentArray Components;
		typedef ComponentArray::iterator ComponentIt;

		GOCId ObjectId;

		//For friend factory only
		GameObjectComposition();
		~GameObjectComposition();
	};

	//Shorter, easier name
	typedef GameObjectComposition GOC;

	template<typename type> type* GameObjectComposition::GetComponentType(ComponentId typeId)
	{
		return static_cast<type*>(GetComponent(typeId));
	}

	#define has(type) GetComponentType<type>( CT_##type )
}
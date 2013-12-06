
#include "Precompiled.h"
#include "Composition.h"
#include <algorithm>

namespace Engine
{
	struct ComponentSorter
	{
		bool operator()(GameComponent* left, GameComponent* right)const
		{
			return left->TypeId < right->TypeId;
		}
	};

	GameComponent* BinaryComponentSearch(ComponentArray& components, ComponentId name)
	{
		size_t begin = 0;
		size_t end = components.size();

		while(begin < end)
		{
			size_t mid = (begin+end) / 2;
			if(components[mid]->TypeId < name)
				begin = mid + 1;
			else
				end = mid;
		}

		if((begin < components.size()) && (components[begin]->TypeId == name))
			return components[begin];
		else
			return NULL;
	}

	void GameObjectComposition::Initialize()
	{
		for(ComponentIt it = Components.begin();it!=Components.end();++it)
		{
			(*it)->Base = this;
			(*it)->Initialize();
		}
	}

	GameObjectComposition::GameObjectComposition()
	{
		ObjectId = 0;
	}

	GameObjectComposition::~GameObjectComposition()
	{
		for(ComponentIt it = Components.begin();it!=Components.end();++it)
			delete *it;
	}

	void GameObjectComposition::AddComponent(ComponentId typeId, GameComponent* component)
	{
		component->TypeId = typeId;
		Components.push_back(component);
	}

	void GameObjectComposition::SendMessage(Message* message)
	{
		for(ComponentIt it = Components.begin();it!=Components.end();++it)
			(*it)->SendMessage(message);
	}

	GameComponent* GameObjectComposition::GetComponent(ComponentId typeId)
	{
		return BinaryComponentSearch(Components, typeId);
	}

	void GameObjectComposition::Destroy()
	{
		//MUST BE FILLED
	}
}
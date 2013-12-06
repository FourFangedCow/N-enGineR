
#pragma once

#include "System.h"
#include "Composition.h"

namespace Engine
{
	class ComponentCreator;

	class GameObjectFactory : public System
	{
	public:
		GameObjectFactory();
		~GameObjectFactory();

		GOC* Create(const std::string &filename);

		void Destroy(GOC* gameObject);

		virtual void Update(float dt);
		virtual std::string GetName(){return "Factory";}
		virtual void SendMessage(Message* message);

		void DestoryAllObjects();

		GOC* CreateEmptyComposition();
		GOC* BuildAndSerialize(const std::string &filename);

		void IdGameObject(GOC* gameObject);
		void AddComponentCreator(const std::string &name, ComponentCreator* creator);

		GOC* GetObjectWithId(GOCId id);

	private:
		unsigned LastGameObjectId;
		typedef std::map<std::string, ComponentCreator*> ComponentMapType;
		ComponentMapType ComponentMap;

		typedef std::map<unsigned, GOC*> GameObjectIdMapType;
		GameObjectIdMapType GameObjectIdMap;

		std::set<GOC*> ObjectsToBeDeleted;
	};

	extern GameObjectFactory* FACTORY;
}
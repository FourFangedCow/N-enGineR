
#include "Precompiled.h"
#include "Factory.h"
#include "Composition.h"
#include "ComponentCreator.h"
#include "TextSerialization.h"

namespace Engine
{
	GameObjectFactory* FACTORY = NULL;

	GameObjectFactory::GameObjectFactory()
	{
		srand(time(NULL));
		FACTORY = this;
		LastGameObjectId = 0;
	}

	GameObjectFactory::~GameObjectFactory()
	{
		for(ComponentMapType::iterator it = ComponentMap.begin();it!=ComponentMap.end();++it)
			delete it->second;
	}

	GOC* GameObjectFactory::CreateEmptyComposition()
	{
		GOC* gameObject = new GOC();
		IdGameObject(gameObject);
		return gameObject;
	}

	void GameObjectFactory::IdGameObject(GOC* gameObject)
	{
		++LastGameObjectId;
		gameObject->ObjectId = LastGameObjectId;
		GameObjectIdMap[LastGameObjectId] = gameObject;
	}

	GOC* GameObjectFactory::GetObjectWithId(GOCId id)
	{
		GameObjectIdMapType::iterator it = GameObjectIdMap.find(id);
		if(it!=GameObjectIdMap.end())
			return it->second;
		else
			return NULL;
	}

	GOC* GameObjectFactory::Create(const std::string &filename)
	{
		GOC* goc = BuildAndSerialize(filename);
		if(goc)
			goc->Initialize();
		return goc;
	}

	void GameObjectFactory::Destroy(GOC* gameObject)
	{
		ObjectsToBeDeleted.insert(gameObject);
	}

	void GameObjectFactory::Update(float dt)
	{
		std::set<GOC*>::iterator it = ObjectsToBeDeleted.begin();
		for(;it!=ObjectsToBeDeleted.end();++it)
		{
			GOC * gameObject = *it;
			GameObjectIdMapType::iterator idItr =  GameObjectIdMap.find(gameObject->ObjectId);
			if( idItr!= GameObjectIdMap.end() )
			{
				delete gameObject;
				GameObjectIdMap.erase( idItr );
			}
		}
		ObjectsToBeDeleted.clear();
	}

	void GameObjectFactory::AddComponentCreator(const std::string &name, ComponentCreator* creator)
	{
		ComponentMap[name] = creator;
	}

	void GameObjectFactory::DestoryAllObjects()
	{
		for(GameObjectIdMapType::iterator it =  GameObjectIdMap.begin();it!=GameObjectIdMap.end();++it)
			delete it->second;

		GameObjectIdMap.clear();
	}

	void GameObjectFactory::SendMessage(Message * message)
	{

	}

	GOC * GameObjectFactory::BuildAndSerialize(const std::string& filename)
	{
		//Open the text file stream serializer
		TextSerializer stream;
		bool fileOpened = stream.Open(filename);
		std::string componentName;

		//Make sure the stream is valid
		if(stream.IsGood())
		{
			//Create a new game object to hold the components
			GOC * gameObject = new GOC();

			while(stream.IsGood())
			{
				//Read the component's name
				StreamRead(stream,componentName);

				//Find the component's creator
				ComponentMapType::iterator it =  ComponentMap.find( componentName );
				if(it != ComponentMap.end())
				{
					//ComponentCreator is an object that creates the component
					ComponentCreator * creator = it->second;

					//Create the component by using the interface
					GameComponent * component = creator->Create();

					//Serialize the component with current stream (this will move
					//the stream to the next component
					//Note: this invokes the base case of serialization in which
					//the object serializes itself. component->Serialize( stream );
					StreamRead(stream,*component);

					//Add the new component to the composition
					gameObject->AddComponent(creator->TypeId , component);
				}
			}

			//Id and initialize the game object composition
			IdGameObject(gameObject);

			return gameObject;
		}

		return NULL;
	}
}
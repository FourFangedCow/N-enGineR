#pragma once

#include "ComponentIds.h"

namespace Engine
{
	//Forward declaration of component
	class GameComponent;

	///Game Component Creator Interface.
	///Used to create components in data driven method in the GameObjectFactory.
	class ComponentCreator
	{
	public:
		ComponentCreator(ComponentId typeId)
			:TypeId(typeId)
		{
		}

		ComponentId TypeId;

		virtual GameComponent * Create()=0;
	};

	template<typename type>
	class ComponentCreatorType : public ComponentCreator
	{
	public:
		ComponentCreatorType(ComponentId typeId)
			:ComponentCreator(typeId)
		{
		}

		virtual GameComponent * Create()
		{
			return new type();
		}
	};

};

//Register component macro
#define RegisterComponent(type) FACTORY->AddComponentCreator( #type, new ComponentCreatorType<type>( CT_##type ) );
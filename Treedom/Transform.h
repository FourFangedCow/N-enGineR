#pragma once

#include "EngineMath.h"
#include "Composition.h"

namespace Engine
{
	class Transform : public GameComponent
	{
	public:
		Transform();
		~Transform(){};

		Vec2D Position;
		float Rotation;
		float Scale;
		void Serialize(Serializer &str);
	};
}
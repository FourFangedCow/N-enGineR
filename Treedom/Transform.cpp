#include "Precompiled.h"
#include "Transform.h"

namespace Engine
{
	Transform::Transform()
	{
		Position = Vec2D(0, 0);
		Rotation = 0.0f;
	}

	void Transform::Serialize(Serializer &stream)
	{
		StreamRead(stream, Position);
		StreamRead(stream, Rotation);
		StreamRead(stream, Scale);
	}
}
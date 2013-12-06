#pragma once

#include "Composition.h"
#include "EngineMath.h"
#include "Transform.h"

namespace Engine
{
	struct c_vert
	{
		float x, y, z;
		DWORD color;
	};


	class Mesh : public GameComponent
	{
	public:
		Mesh();

		std::vector<c_vert> vertList;
		Transform* transform;
		int num;
		Mesh* parent;

		void Initialize();
		void Draw();
		void Serialize(Serializer &str);

		void AddToVertList(c_vert vertex) { vertList.push_back(vertex); }
		c_vert GetVertex(int index) { return vertList[index]; }

		//SPECIAL VARIABLES

		//SPECIAL MOVEMENTS

	protected:
		virtual ~Mesh() {};
	};

	inline void StreamRead(Serializer& stream, c_vert& v)
	{
		int r, g, b;
		StreamRead(stream,v.x);
		StreamRead(stream,v.y);
		StreamRead(stream,v.z);
		StreamRead(stream,r);
		StreamRead(stream,g);
		StreamRead(stream,b);

		v.color = D3DCOLOR_XRGB(r, g, b);
	}
}
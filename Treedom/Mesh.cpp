
#include "Precompiled.h"
#include "Mesh.h"
#include "Graphics.h"

namespace Engine
{
	Mesh::Mesh()
	{
		transform = NULL;
		num = 1;
		parent = NULL;
	}

	void Mesh::Serialize(Serializer &stream)
	{
		c_vert in;
		int num;
		StreamRead(stream, num);
		for(int i = 0; i < num; i++)
		{
			StreamRead(stream, in);
			vertList.push_back(in);
		}
	}

	void Mesh::Initialize()
	{
		transform = GetOwner()->has(Transform);
		GRAPHICS->meshList.push_back(this);
	}

	void Mesh::Draw()
	{
		unsigned int nSizeOfData = vertList.size() * sizeof(CUSTOMVERTEX);
		const DWORD dwLockFlags = D3DLOCK_DISCARD;
		BYTE* pBytes;
		GRAPHICS->v_buffer->Lock(0, 0, (void**)&pBytes, dwLockFlags);
		if(!(&vertList[0]))
			printf("Buffer 0 Error\n");
		else
			memcpy(pBytes, &vertList[0], nSizeOfData);
		GRAPHICS->v_buffer->Unlock();
	}
}
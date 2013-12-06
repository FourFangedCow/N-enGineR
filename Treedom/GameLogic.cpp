
#include "Precompiled.h"
#include "GameLogic.h"
#include "Factory.h"
#include "ComponentCreator.h"

namespace Engine
{
	float offset = 0.1f;
	int numObj = 0;
	int count = 100;
	GOC* PLAYER = NULL;

	void GameLogic::Initialize()
	{
		GOC* temp;
		RegisterComponent(Mesh);
		RegisterComponent(BranchingMesh);
		RegisterComponent(Transform);
		temp = FACTORY->Create("Objects//Square.txt");

		/* Branching Mesh */
		/*GOC* obj = FACTORY->Create("Objects//Triangle.txt");
		Transform* trans = obj->has(Transform);
		trans->Position.x += 7;
		meshList.push_back(obj->has(BranchingMesh));*/
		
	}
	void GameLogic::Update(float dt)
	{
		for(std::list<BranchingMesh*>::iterator iter = meshList.begin(); iter != meshList.end(); ++iter)
		{
			BranchingMesh* temp = *iter;
			temp->Grow(200);
			temp->Wave(100, 0.004f);
		}

		
		if(count > 1 && offset < 14)
		{
			GOC* obj = FACTORY->Create("Objects//Triangle.txt");
			Transform* trans = obj->has(Transform);
			trans->Position.x += offset;
			meshList.push_back(obj->has(BranchingMesh));
			offset += 0.01f;
			count = 0;
			printf("NUM OBJECTS: %i\n", ++numObj);
		}
		count++;
	}
}
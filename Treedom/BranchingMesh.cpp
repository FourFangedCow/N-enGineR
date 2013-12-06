
#include "Precompiled.h"
#include "BranchingMesh.h"


namespace Engine
{
	BranchingMesh::BranchingMesh() : Mesh() 
	{
		width = 0;
		dev = (float)(rand() % 1) / 1000;
		dir = false;
		waveDir = false;
		waveNum = 0;
		waveDev = 0;
		waveCycles = 0;
	}
	void BranchingMesh::Grow(int time)
	{
		if(num > time)
			return;
	
		Transform* trans = this->GetOwner()->has(Transform);
		c_vert newVert;
		
		trans->Position.y += 0.025f;
		trans->Position.x -= (dev);
		
		if(width > 0)
		{
			width += (float)(rand() % 5) / 1000;
			newVert.x = GetVertex(num + 1).x + width + dev;
		}
		else
		{
			width -= (float)(rand() % 5) / 1000;
			newVert.x = GetVertex(num + 1).x + width + dev;
		}
		if(abs(dev) > 0.0001 && !dir)
			dir = true;
		else if(abs(dev) > 0.0001 && dir)
			dir = false;
		if(dir)
			dev += (float)(rand() % 2) / 1000.0f;
		else
			dev -= (float)(rand() % 2) / 1000.0f;//0.0001;
	
		newVert.y = GetVertex(num).y - 0.05f;
		newVert.z = GetVertex(num).z;
		newVert.color = D3DCOLOR_XRGB(rand() % 255, rand() % 255, rand() % 255);
		num++;
		width *= -1;
		AddToVertList(newVert);
	}
	void BranchingMesh::Wave(int numOfVerts, float dev)
	{
		float offset;
		if(numOfVerts > num)
			return;

		for(std::vector<c_vert>::iterator iter = vertList.begin(); iter != vertList.end(); iter++) 
		{
			waveDev += 0.00002f;
			
			
			if(dev - waveDev < 0 )
			{
				waveCycles++;
				waveDev = 0;
				if(waveDir && waveCycles > numOfVerts)
				{
					waveDir = false;
					waveCycles = 0;
				}
				else if(waveCycles > numOfVerts)
				{
					waveDir = true;
					waveCycles = 0;
				}
				return;
			}
			offset = ((float)(waveCycles - ((float)numOfVerts / 2)) / (float)numOfVerts);
			if(waveDir)
				iter->x += (dev - waveDev) * (0.5f - abs(offset));
			else
				iter->x -= (dev - waveDev) * (0.5f - abs(offset)); 
		}
	}
	void BranchingMesh::Sprout()
	{

	}
}
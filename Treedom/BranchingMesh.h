
#pragma once

#include "Mesh.h"

namespace Engine
{
	class BranchingMesh : public Mesh
	{
	public:
		BranchingMesh();
		~BranchingMesh() {};
		
		void Grow(int times);
		void Wave(int numOfVerts, float dev);
		void Sprout();

		float width, dev, waveDev, ranDev;
		bool dir, waveDir;
		int waveNum, waveCycles;
	};
}
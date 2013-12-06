#include "Graphics.h"
#include "Engine.h"

namespace Engine
{
	class GameLogic : public System
	{
		std::list<BranchingMesh*> meshList;

		virtual void Initialize();
		virtual void Update(float dt);
		virtual std::string GetName() {return "GameLogic";}
	};

	extern GOC* PLAYER;
}

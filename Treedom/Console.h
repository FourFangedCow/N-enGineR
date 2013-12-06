
#include "Engine.h"


namespace Engine
{
	class DebugConsole : public System
	{
	public:
		DebugConsole();
		~DebugConsole() {};

		virtual void Update(float dt) {};
		virtual std::string GetName() {return "DebugConsole";}

	};
}
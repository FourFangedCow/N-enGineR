
#include "Console.h"


namespace Engine
{
	DebugConsole::DebugConsole()
	{
		if(AllocConsole())
		{
			freopen("CONOUT$", "wt", stdout);
			
			SetConsoleTitle("Debug Console");

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
		}
	}
}
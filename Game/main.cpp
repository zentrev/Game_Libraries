#include "engine.h"

int main(int argc, char* argv[])
{
	Engine engine;

	engine.Initialize();
	while (!engine.IsQuit())
	{
		engine.Update();
	}
	engine.Shutdown();
	//engine.Display();

	return 0;
}
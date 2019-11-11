#include "InitClose.h"
#include "Game.h"
#include <iostream>

using namespace IsoEngine;

int main(int argc, char* argv[])
{
	InitClose::InitSDL("Game");
	Game::instance().Init();

	while (!Game::instance().quit)
	{
		Game::instance().Update();
		Game::instance().UpdateInput();
		Game::instance().Draw();
	}

	Game::instance().Shutdown();
	InitClose::ShutdownSDL();
	return 0;
}
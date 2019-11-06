#include "InitClose.h"
#include "Game.h"
#include <iostream>

using namespace IsoEngine;

int main(int argc, char* argv[])
{
	InitClose::InitSDL("Game");
	Game game;
	game.Init();

	while (!game.quit)
	{
		game.Update();
		game.UpdateInput(game);
		game.Draw();
	}

	InitClose::ShutdownSDL();
	return 0;
}
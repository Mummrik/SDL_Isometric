#include <SDL.h>
#include "initclose.h"
#include "renderer.h"


//Tutorial video https://www.youtube.com/watch?v=8xf_ouTpd1c
//timestamp 36:54
typedef struct gameT
{
	SDL_Event event;
	int loopDone;
}gameT;

gameT game;

void Init()
{
	game.loopDone = 0;
}

void Draw()
{
	SDL_SetRenderDrawColor(GetRenderer(), 0x3b, 0x3b, 0x3b, 0x00);
	SDL_RenderClear(GetRenderer());
	SDL_RenderPresent(GetRenderer());
	SDL_Delay(10);
}

void Update()
{

}

void UpdateInput()
{
	while (SDL_PollEvent(&game.event) != 0)
	{
		switch (game.event.type)
		{
		case SDL_QUIT:
			game.loopDone = 1;
			break;
		case SDL_KEYUP:
			switch (game.event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				game.loopDone = 1;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	InitSDL("Title");

	while (!game.loopDone)
	{
		Update();
		UpdateInput();
		Draw();
	}

	CloseDownSDL();
	return 0;
}
#include <SDL.h>
#include <SDL_image.h>
#include "initclose.h"
#include "renderer.h"
#include <stdio.h>

void InitSDL(const char* windowName)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Could not initialize SDL! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");

	if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0"))
	{
		fprintf(stdout, "Warning: Linear texture filtering was not enabled!\n");
	}

	InitRenderer(windowName);

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		fprintf(stderr, "Could not Initialize SDL_Image! SDL_image: %s\n", IMG_GetError());
		exit(1);
	}
}

void CloseDownSDL()
{
	CloseRenderer();
	IMG_Quit();
	SDL_Quit();
}
#include <SDL.h>
#include "renderer.h"
#include <stdio.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

void InitRenderer(const char* windowCaption)
{
	window = SDL_CreateWindow(windowCaption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow failed: %s", SDL_GetError());
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer failed: %s", SDL_GetError());
		exit(1);
	}
}

SDL_Renderer* GetRenderer()
{
	return renderer;
}

SDL_Window* GetWindow()
{
	return window;
}

void CloseRenderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
}
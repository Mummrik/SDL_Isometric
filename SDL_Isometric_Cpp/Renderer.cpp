#include "Renderer.h"
#include <stdio.h>
#include <string>

namespace IsoEngine
{
	bool Renderer::Init(const char* title)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (!window)
		{
			fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
			//exit(1);
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer)
		{
			fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
			//exit(1);
			return false;
		}

		return true;
	}

	void Renderer::Shutdown()
	{
		if (renderer)
		{
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
		}

		if (window)
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}

		if (&instance())
		{
			delete& instance();
		}
	}
}
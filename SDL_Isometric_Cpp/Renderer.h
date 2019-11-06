#pragma once

#include <SDL.h>

#define WINDOW_HEIGHT	700
#define WINDOW_WIDTH	1200

namespace IsoEngine
{
	class Renderer
	{
	public:
		SDL_Window* GetWindow() { return window; }
		SDL_Renderer* GetRenderer() { return renderer; }
		bool Init(const char* title);
		void Shutdown();

	protected:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
	};
}


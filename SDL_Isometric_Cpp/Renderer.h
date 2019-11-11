#pragma once

#include <SDL.h>

#define WINDOW_HEIGHT	700
#define WINDOW_WIDTH	1200

namespace IsoEngine
{
	class Renderer
	{
	public:
		static Renderer& instance()
		{
			static Renderer* instance = new Renderer();
			return *instance;
		}


		SDL_Window* GetWindow() const { return window; }
		SDL_Renderer* GetRenderer() const { return renderer; }
		bool Init(const char* title);
		void Shutdown();

	protected:
		Renderer() {}
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		static Renderer* _instance;
	};
}


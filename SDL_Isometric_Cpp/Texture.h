#pragma once
#include <SDL.h>

namespace IsoEngine
{
	class Renderer;
	class Texture
	{
	public:
		int x;
		int y;
		int width;
		int height;
		double angle;
		SDL_Point* center;
		SDL_Rect* clipRect;
		SDL_RendererFlip flipType;
		SDL_Texture* texture;

		static int Load(Texture* texture, const char* fileName);
		static void Init(Texture* texture, int x, int y, double angle, SDL_Point* center, SDL_Rect* clipRect, SDL_RendererFlip flipType);
		static void RendererXYClip(Texture* texture, int x, int y, SDL_Rect* clipRect);

	};
}


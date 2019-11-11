#include "Texture.h"
#include "Renderer.h"

#include <SDL_image.h>
#include <stdio.h>

namespace IsoEngine
{
	int Texture::Load(Texture* texture, const char* fileName)
	{
		SDL_Surface* tmpSurface = IMG_Load(fileName);
		if (!tmpSurface)
		{
			fprintf(stderr, "Texture Error: Couldn't load image: %s! SDL_image Error: %s\n", fileName, IMG_GetError());
			return 0;
		}
		else
		{
			texture->texture = SDL_CreateTextureFromSurface(Renderer::instance().GetRenderer(), tmpSurface);

			if (!texture->texture)
			{
				fprintf(stderr, "Texture Error: Couldn't load image: %s! SDL_image Error: %s\n", fileName, IMG_GetError());
				SDL_FreeSurface(tmpSurface);
				return 0;
			}
			else
			{
				texture->width = tmpSurface->w;
				texture->height = tmpSurface->h;
			}
			SDL_FreeSurface(tmpSurface);
			return 1;
		}

		return 0;
	}
	void Texture::Init(Texture* texture, int x, int y, double angle, SDL_Point* center, SDL_Rect* clipRect, SDL_RendererFlip flipType)
	{
		texture->x = x;
		texture->y = y;
		texture->angle = angle;
		texture->center = center;
		texture->clipRect = clipRect;
		texture->flipType = flipType;
	}
	void Texture::RendererXYClip(Texture* texture, int x, int y, SDL_Rect* clipRect)
	{
		if (!texture)
		{
			fprintf(stderr, "Warning: passed texture didn't exist!\n");
			return;
		}

		texture->x = x;
		texture->y = y;
		texture->clipRect = clipRect;
		SDL_Rect quad = { texture->x, texture->y, texture->width, texture->height };

		if (!texture->clipRect)
		{
			quad.w = texture->clipRect->w;
			quad.h = texture->clipRect->h;
		}

		SDL_RenderCopyEx(Renderer::instance().GetRenderer(), texture->texture, texture->clipRect, &quad, texture->angle, texture->center, texture->flipType);
	}
}
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "texture.h"
#include "renderer.h"

int LoadTexture(textureT* texture, const char* fileName)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);

	if (tmpSurface == NULL)
	{
		fprintf(stderr, "Texture Error: Could not load image: %s! SDL_image Error: %d\n", fileName, IMG_GetError());
		return 0;
	}
	else
	{
		texture->texture = SDL_CreateTextureFromSurface(GetRenderer(), tmpSurface);

		if (texture->texture == NULL)
		{
			fprintf(stderr, "Texture Error: Could not load image: %s! SDL_image Error: %d\n", fileName, IMG_GetError());
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

void TextureInit(textureT* texture, int x, int y, double angle, SDL_Point* center, SDL_Rect* clipRect, SDL_RendererFlip flipType)
{
	texture->x = x;
	texture->y = y;
	texture->angle = angle;
	texture->center = center;
	texture->clipRect = clipRect;
	texture->flipType = flipType;
}

void textureRenderXYClip(textureT* texture, int x, int y, SDL_Rect* clipRect)
{
	if (texture == NULL)
	{
		fprintf(stderr, "Warning: passed texture was NULL!\n");
		return;
	}
	texture->x = x;
	texture->y = y;
	texture->clipRect = clipRect;
	SDL_Rect quad = { texture->x,texture->y,texture->width,texture->height };
}
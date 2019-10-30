#pragma once

typedef struct textureT
{
	int x;
	int y;
	int width;
	int height;
	double angle;
	SDL_Point* center;
	SDL_Rect* clipRect;
	SDL_RendererFlip flipType;
	SDL_Texture* texture;
}textureT;


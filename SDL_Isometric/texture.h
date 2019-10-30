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

int LoadTexture(textureT* texture, const char* fileName);
void TextureInit(textureT* texture, int x, int y, double angle, SDL_Point* center, SDL_Rect* clipRect, SDL_RendererFlip flipType);
void TextureRenderXYClip(textureT* texture, int x, int y, SDL_Rect* clipRect);
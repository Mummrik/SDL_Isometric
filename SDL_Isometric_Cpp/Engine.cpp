#include "Engine.h"

#include <stdio.h>

namespace IsoEngine
{
	unsigned int Engine::TILESIZE = 0;
	int Engine::scrollX = 0;
	int Engine::scrollY = 0;
	int Engine::mapWidth = 0;
	int Engine::mapHeight = 0;

	void Engine::Init(int tileSize)
	{
		if (tileSize <= 0)
		{
			TILESIZE = 32;
		}
		else
		{
			TILESIZE = tileSize;
		}
	}
	void Engine::SetMapSize(int width, int height)
	{
		mapHeight = height;
		mapWidth = width;
	}
	void Engine::Convert2DToIso(Vector2D* vector2D)
	{
		int tmpX = vector2D->x - vector2D->y;
		int tmpY = (vector2D->x + vector2D->y) * 0.5f;

		vector2D->x = tmpX;
		vector2D->y = tmpY;
	}
	void Engine::ConvertIsoTo2D(Vector2D* vector2D)
	{
		int tmpX = ((2 * vector2D->y) + vector2D->x) * 0.5f;
		int tmpY = ((2 * vector2D->y) - vector2D->x) * 0.5f;

		vector2D->x = tmpX;
		vector2D->y = tmpY;

	}
	void Engine::GetTileCoordinates(Vector2D* vector2D, Vector2D* vector2DCoord)
	{
		float tmpX = (float)vector2D->x / (float)TILESIZE;
		float tmpY = (float)vector2D->y / (float)TILESIZE;

		vector2DCoord->x = (int)tmpX;
		vector2DCoord->y = (int)tmpY;
	}
}
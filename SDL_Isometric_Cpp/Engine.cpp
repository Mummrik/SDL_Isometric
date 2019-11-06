#include "Engine.h"

#include <stdio.h>

namespace IsoEngine
{
	void Engine::Init(Engine* engine, int tileSize)
	{
		if (!engine)
		{
			fprintf(stderr, "Error in Engine::Init(...): engine parameter is NULL!\n");
			return;
		}

		if (tileSize <= 0)
		{
			//engine->TILESIZE = 32;
			TILESIZE = 32;
		}
		else
		{
			//engine->TILESIZE = tileSize;
			TILESIZE = tileSize;
		}

		engine->mapHeight = 0;
		engine->mapWidth = 0;
		engine->scrollX = 0;
		engine->scrollY = 0;
	}
	void Engine::SetMapSize(Engine* engine, int width, int height)
	{
		if (!engine)
		{
			fprintf(stderr, "Error in Engine::SetMapSize(...): engine parameter is NULL!\n");
			return;
		}
		engine->mapHeight = height;
		engine->mapWidth = width;
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
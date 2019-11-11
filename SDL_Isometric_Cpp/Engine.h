#pragma once
#include "Vector2D.h"

#define NUM_ISOMETRIC_TILES 5
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

namespace IsoEngine
{
	class Engine
	{
	public:
		static unsigned int TILESIZE;
		static int scrollX;
		static int scrollY;
		static int mapWidth;
		static int mapHeight;

		static void Init(int tileSize);
		static void SetMapSize(int width, int height);
		static void Convert2DToIso(Vector2D* vector2D);
		void ConvertIsoTo2D(Vector2D* vector2D);
		void GetTileCoordinates(Vector2D* vector2D, Vector2D* vector2DCoord);	// Note: Rename parameter names later!
	};
}


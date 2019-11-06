#pragma once
#include "Vector2D.h"

namespace IsoEngine
{
	class Engine
	{
	public:
		unsigned int TILESIZE;
		int scrollX;
		int scrollY;
		int mapWidth;
		int mapHeight;

		void Init(Engine* engine, int tileSize);
		void SetMapSize(Engine* engine, int width, int height);
		void Convert2DToIso(Vector2D* vector2D);
		void ConvertIsoTo2D(Vector2D* vector2D);
		void GetTileCoordinates(Vector2D* vector2D, Vector2D* vector2DCoord);	// Note: Rename parameter names later!
	};
}


#pragma once
#include <SDL.h>

#include "Vector2D.h"
#include "Engine.h"
#include "Texture.h"

namespace IsoEngine
{
	class Game
	{
	public:
		static Game& instance()
		{
			static Game* instance = new Game();
			return *instance;
		}

		SDL_Event event;
		bool quit;
		SDL_Rect mouseRect;
		Vector2D mousePoint;
		Vector2D mapScroll2DPos;
		float mapScrollSpeed;
		Engine engine;
		Texture tilesTex;
		SDL_Rect tilesRects[NUM_ISOMETRIC_TILES];
		int lastTileClicked;
		int world[MAP_HEIGHT][MAP_WIDTH];

		void Init();
		void Shutdown();
		void Draw();
		void Update();
		void UpdateInput();

		void InitTileClip();
		void DrawIsoMap(Engine* engine);
		void SetupRect(SDL_Rect* rect, int x, int y, int w, int h);
		void SetupWorldMap();
	private:
		Game() {}

	};
}

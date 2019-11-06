#pragma once
#include <SDL.h>

#include "Vector2D.h"
#include "Engine.h"

namespace IsoEngine
{
	class Game
	{
	public:
		SDL_Event event;
		bool quit;
		SDL_Rect mouseRect;
		Vector2D mousePoint;
		Vector2D mapScroll2DPos;
		float mapScrollSpeed;
		Engine engine;
		int lastTileClicked;

		void Init();
		void Draw();
		void Update();
		void UpdateInput(Game game);

	};
}

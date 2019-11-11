#include "Game.h"
#include "Renderer.h"

#include <cstdlib>
#include <cstdio>

namespace IsoEngine
{
	void Game::Init()
	{
		quit = false;
		InitTileClip();
		Engine::Init(64);
		Engine::SetMapSize(MAP_WIDTH, MAP_HEIGHT);
		SetupWorldMap();

		engine.scrollX = (engine.TILESIZE * 9) + 16;
		engine.scrollY = -engine.scrollX;
		mapScroll2DPos.x = -engine.scrollX;
		mapScroll2DPos.y = 0;
		mapScrollSpeed = 3;
		lastTileClicked = -1;

		if (Texture::Load(&tilesTex, "data/isotiles.png") == 0)
		{
			fprintf(stderr, "Error, could not load texture: data/isotiles.png\n");
			//exit(1);
		}
	}
	void Game::Shutdown()
	{
		if (&instance())
		{
			delete& instance();
		}
	}
	void Game::Draw()
	{
		SDL_SetRenderDrawColor(Renderer::instance().GetRenderer(), 0x3b, 0x3b, 0x3b, 0x00);
		SDL_RenderClear(Renderer::instance().GetRenderer());


		DrawIsoMap(&engine);

		/*DrawIsoMouse();

		if (game.lastTileClicked != -1)
		{
			TextureRenderXYClip(&tilesTex, 0, 0, &tilesRects[game.lastTileClicked]);
		}*/

		SDL_RenderPresent(Renderer::instance().GetRenderer());
		SDL_Delay(10);

	}
	void Game::Update()
	{
	}
	void Game::UpdateInput()
	{
		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					//GetMouseTileClick(&game.isoEngine);
				}
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					if (lastTileClicked > -1)
					{
						lastTileClicked = -1;
					}
				}
				break;
			default:
				break;
			}
		}
		if (keyState[SDL_SCANCODE_W])
		{
			engine.scrollX += mapScrollSpeed;
			engine.scrollY += mapScrollSpeed;
			mapScroll2DPos.y += mapScrollSpeed;

			if (mapScroll2DPos.y > 0)
			{
				mapScroll2DPos.y = 0;
				engine.scrollX -= mapScrollSpeed;
				engine.scrollY -= mapScrollSpeed;
			}
		}
		if (keyState[SDL_SCANCODE_A])
		{
			engine.scrollX += mapScrollSpeed;
			engine.scrollY -= mapScrollSpeed;
			mapScroll2DPos.x -= mapScrollSpeed;
		}
		if (keyState[SDL_SCANCODE_S])
		{
			engine.scrollX -= mapScrollSpeed;
			engine.scrollY -= mapScrollSpeed;
			mapScroll2DPos.y -= mapScrollSpeed;
		}
		if (keyState[SDL_SCANCODE_D])
		{
			engine.scrollX -= mapScrollSpeed;
			engine.scrollY += mapScrollSpeed;
			mapScroll2DPos.x += mapScrollSpeed;
		}
	}
	void Game::InitTileClip()
	{
		int x = 0, y = 0;

		Texture::Init(&tilesTex, 0, 0, 0, NULL, NULL, SDL_FLIP_NONE);

		for (int i = 0; i < NUM_ISOMETRIC_TILES; i++)
		{
			SetupRect(&tilesRects[i], x, y, 64, 80);
			x += 64;
		}
	}
	void Game::DrawIsoMap(Engine* engine)
	{
		int tile;
		Vector2D vector2D;

		for (int y = 0; y < engine->mapHeight; y++)
		{
			for (int x = 0; x < engine->mapWidth; x++)
			{
				vector2D.x = (x * engine->TILESIZE) + engine->scrollX;
				vector2D.y = (y * engine->TILESIZE) + engine->scrollY;

				tile = world[y][x];

				Engine::Convert2DToIso(&vector2D);

				Texture::RendererXYClip(&tilesTex, vector2D.x, vector2D.y, &tilesRects[tile]);

			}
		}
	}
	void Game::SetupRect(SDL_Rect* rect, int x, int y, int w, int h)
	{
		*rect = { x,y,w,h };
	}
	void Game::SetupWorldMap()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				int rndTile = rand() % NUM_ISOMETRIC_TILES;
				if (rndTile <= 0)
				{
					rndTile = 1;
				}
				world[y][x] = rndTile;
			}
		}
	}
}
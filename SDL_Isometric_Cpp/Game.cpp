#include "Game.h"
#include "Renderer.h"

namespace IsoEngine
{
	void Game::Init()
	{
		quit = false;
	}
	void Game::Draw()
	{
		Renderer renderer = IsoEngine::Renderer();
		SDL_SetRenderDrawColor(renderer.GetRenderer(), 0x3b, 0x3b, 0x3b, 0x00);
		SDL_RenderClear(renderer.GetRenderer());

		/*
		DrawIsoMap(&game.isoEngine);
		DrawIsoMouse();

		if (game.lastTileClicked != -1)
		{
			TextureRenderXYClip(&tilesTex, 0, 0, &tilesRects[game.lastTileClicked]);
		}*/

		SDL_RenderPresent(renderer.GetRenderer());
		SDL_Delay(10);

	}
	void Game::Update()
	{
	}
	void Game::UpdateInput(Game game)
	{
		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&game.event) != 0)
		{
			switch (game.event.type)
			{
			case SDL_QUIT:
				game.quit = true;
				break;
			case SDL_KEYUP:
				switch (game.event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					game.quit = true;
					break;
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (game.event.button.button == SDL_BUTTON_LEFT)
				{
					//GetMouseTileClick(&game.isoEngine);
				}
				if (game.event.button.button == SDL_BUTTON_RIGHT)
				{
					if (game.lastTileClicked > -1)
					{
						game.lastTileClicked = -1;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}
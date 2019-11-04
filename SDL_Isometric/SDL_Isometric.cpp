#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "initclose.h"
#include "renderer.h"
#include "texture.h"
#include "isoEngine.h"


//Tutorial video https://www.youtube.com/watch?v=8xf_ouTpd1c
//timestamp 36:54
// timestamp 1:15:26

#define NUM_ISOMETRIC_TILES 5
#define MAP_HEIGHT 100
#define MAP_WIDTH 100

int world[MAP_HEIGHT][MAP_WIDTH];

typedef struct gameT
{
	SDL_Event event;
	int loopDone;
	SDL_Rect mouseRect;
	point2DT mousePoint;
	point2DT mapScroll2DPos;
	int mapScrollSpeed;
	isoEngineT isoEngine;
	int lastTileClicked;

}gameT;

gameT game;
textureT tilesTex;
SDL_Rect tilesRects[NUM_ISOMETRIC_TILES];

void SetupWorldMap()
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

void SetupRect(SDL_Rect* rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

void InitTileClip()
{
	int x = 0, y = 0;

	TextureInit(&tilesTex, 0, 0, 0, NULL, NULL, SDL_FLIP_NONE);

	for (int i = 0; i < NUM_ISOMETRIC_TILES; i++)
	{
		// 64x80 tile size
		SetupRect(&tilesRects[i], x, y, 64, 80);
		x += 64;
	}
}

void Init()
{
	int tileSize = 64;
	game.loopDone = 0;
	InitTileClip();
	InitIsoEngine(&game.isoEngine, tileSize);
	IsoEngineSetMapSize(&game.isoEngine, MAP_WIDTH, MAP_HEIGHT);
	SetupWorldMap();

	game.isoEngine.scrollX = (TILESIZE * 9) + 16;
	game.isoEngine.scrollY = -game.isoEngine.scrollX;
	game.mapScroll2DPos.x = -game.isoEngine.scrollX;
	game.mapScroll2DPos.y = 0;
	game.mapScrollSpeed = 3;
	game.lastTileClicked = -1;

	if (LoadTexture(&tilesTex, "data/isotiles.png") == 0)
	{
		fprintf(stderr, "Error, could not load texture: data/isotiles.png\n");
		exit(1);
	}
}

void DrawIsoMouse()
{
	int correctX = (game.mapScroll2DPos.x % TILESIZE) * 2;
	int correctY = (game.mapScroll2DPos.y % TILESIZE);

	game.mousePoint.x = (game.mouseRect.x / TILESIZE) * TILESIZE;
	game.mousePoint.y = (game.mouseRect.y / TILESIZE) * TILESIZE;

	// For every other X position on the map
	if ((game.mousePoint.x / TILESIZE) % 2)
	{
		// move the mouse down by half a tile so can pick isometric tiles on that row as well
		game.mousePoint.y += TILESIZE * 0.5;
	}
	TextureRenderXYClip(&tilesTex, game.mousePoint.x - correctX, game.mousePoint.y + correctY, &tilesRects[0]);
}

void DrawIsoMap(isoEngineT* isoEngine)
{
	int tile;
	point2DT point;

	for (int y = 0; y < isoEngine->mapHeight; y++)
	{
		for (int x = 0; x < isoEngine->mapWidth; x++)
		{
			point.x = (x * TILESIZE) + isoEngine->scrollX;
			point.y = (y * TILESIZE) + isoEngine->scrollY;

			tile = world[y][x];

			Convert2DToIso(&point);
			TextureRenderXYClip(&tilesTex, point.x, point.y, &tilesRects[tile]);
		}
	}
}

void GetMouseTileClick(isoEngineT* isoEngine)
{
	point2DT point;
	point2DT tileShift, mouseToIsoPoint;

	int correctX = (game.mapScroll2DPos.x % TILESIZE) * 2;
	int correctY = (game.mapScroll2DPos.y % TILESIZE);

	// copy mouse point
	mouseToIsoPoint = game.mousePoint;
	ConvertIsoTo2D(&mouseToIsoPoint);

	//get tile coordinates
	GetTileCoordinates(&mouseToIsoPoint, &point);

	tileShift.x = correctX;
	tileShift.y = correctY;
	//ConvertIsoTo2D(&tileShift);
	Convert2DToIso(&tileShift);

	point.x -= ((float)isoEngine->scrollX + (float)tileShift.x) / (float)TILESIZE;
	point.y -= ((float)isoEngine->scrollY - (float)tileShift.y) / (float)TILESIZE;

	if (point.x >= 0 && point.y >= 0 && point.x < MAP_WIDTH && point.y > MAP_HEIGHT)
	{
		game.lastTileClicked = world[point.y][point.x];
	}

	game.lastTileClicked = world[point.y][point.x];
}

void Draw()
{
	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(GetRenderer(), 0x3b, 0x3b, 0x3b, 0x00);
	SDL_RenderClear(GetRenderer());

	DrawIsoMap(&game.isoEngine);
	DrawIsoMouse();

	if (game.lastTileClicked != -1)
	{
		TextureRenderXYClip(&tilesTex, 0, 0, &tilesRects[game.lastTileClicked]);
	}

	SDL_RenderPresent(GetRenderer());
	SDL_Delay(10);
}

void Update()
{
	SDL_GetMouseState(&game.mouseRect.x, &game.mouseRect.y);
}

void UpdateInput()
{
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&game.event) != 0)
	{
		switch (game.event.type)
		{
		case SDL_QUIT:
			game.loopDone = 1;
			break;
		case SDL_KEYUP:
			switch (game.event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				game.loopDone = 1;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (game.event.button.button == SDL_BUTTON_LEFT)
			{
				GetMouseTileClick(&game.isoEngine);
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
	if (keyState[SDL_SCANCODE_W])
	{
		game.isoEngine.scrollX += game.mapScrollSpeed;
		game.isoEngine.scrollY += game.mapScrollSpeed;
		game.mapScroll2DPos.y += game.mapScrollSpeed;

		if (game.mapScroll2DPos.y > 0)
		{
			game.mapScroll2DPos.y = 0;
			game.isoEngine.scrollX -= game.mapScrollSpeed;
			game.isoEngine.scrollY -= game.mapScrollSpeed;
		}
	}
	if (keyState[SDL_SCANCODE_A])
	{
		game.isoEngine.scrollX += game.mapScrollSpeed;
		game.isoEngine.scrollY -= game.mapScrollSpeed;
		game.mapScroll2DPos.x -= game.mapScrollSpeed;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		game.isoEngine.scrollX -= game.mapScrollSpeed;
		game.isoEngine.scrollY -= game.mapScrollSpeed;
		game.mapScroll2DPos.y -= game.mapScrollSpeed;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		game.isoEngine.scrollX -= game.mapScrollSpeed;
		game.isoEngine.scrollY += game.mapScrollSpeed;
		game.mapScroll2DPos.x += game.mapScrollSpeed;
	}
}

int main(int argc, char* argv[])
{
	InitSDL("Title");
	Init();

	while (!game.loopDone)
	{
		Update();
		UpdateInput();
		Draw();
	}

	CloseDownSDL();
	return 0;
}
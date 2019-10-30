#pragma once

#define WINDOW_HEIGHT	700
#define WINDOW_WIDTH	1200

void CloseRenderer();
SDL_Window* GetWindow();
SDL_Renderer* GetRenderer();
void InitRenderer(const char* windowCaption);
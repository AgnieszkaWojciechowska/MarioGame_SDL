#pragma once
#include "window.h"

int init_window(window_scr& wind)
{
	int ret = -505;
	if(ret = set_window_mode(wind))
		window_settings(wind);
	return ret;
}

int set_window_mode(window_scr& wind)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		return -105;
	}
	// tryb pe³noekranowy
	//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
	//	                                 &window, &renderer);
	wind.rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&wind.window, &wind.renderer);

	if (wind.rc != 0)
	{
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return -106;
	};
	return 1;
}


void window_settings(window_scr& wind)
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(wind.renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(wind.renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(wind.window, "Szablon do zdania drugiego 2014");


	wind.screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	wind.scrtex = SDL_CreateTexture(wind.renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);
}

void quit_window(window_scr& wind)
{
	// zwolnienie powierzchni
	SDL_FreeSurface(wind.charset);
	SDL_FreeSurface(wind.screen);
	SDL_DestroyTexture(wind.scrtex);
	SDL_DestroyRenderer(wind.renderer);
	SDL_DestroyWindow(wind.window);

	SDL_Quit();
}
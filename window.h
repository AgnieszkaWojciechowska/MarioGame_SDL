#pragma once
#define _USE_MATH_DEFINES

#include<math.h>
#include<stdio.h>
#include<string.h>
extern "C" {
	//#ifdef BIT64
	//#include"./sdl64/include/SDL.h"
	//#include"./sdl64/include/SDL_main.h"
	//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
	//#endif
}


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

struct window_scr
{
	int rc;					
	SDL_Event event;
	SDL_Surface *screen, *charset;
	int i;			//do info
	
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
};
/*wczytanie okna*/
int init_window(window_scr& wind);
/*ustawienie trybu okna*/
int set_window_mode(window_scr& wind);
/*wczytanie ustawien okna*/
void window_settings(window_scr& wind);
/*wyjscie z gry i zwolnienie pamieci*/
void quit_window(window_scr& wind);
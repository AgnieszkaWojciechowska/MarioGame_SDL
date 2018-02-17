#pragma once
#define _USE_MATH_DEFINES
#ifndef window
#include "window.h"
#endif
#include<math.h>
#include<stdio.h>
#include<string.h>

#define CZAS_GRY 300 //sekund

struct grafics
{
	SDL_Surface *tlo;
	SDL_Surface *podloga;
	SDL_Surface *niebo;
	SDL_Surface *ico;
	SDL_Surface *ico_r1;
	SDL_Surface *ico_r2;
	SDL_Surface *ico_r3;
	SDL_Surface *ico_l1;
	SDL_Surface *ico_l2;
	SDL_Surface *ico_l3;
	SDL_Surface *ico_j;
	SDL_Surface *goom_1;
	SDL_Surface *goom_2;
	SDL_Surface *goom_3;
	SDL_Surface *end;

};


/*wczytanie okna*/
void init_graph(window_scr& wind, grafics& graph);

// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
	SDL_Surface *charset);


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y, int destx, int desty);


// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);


// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);


// rysowanie prostok¹ta o d³ugoœci boków l i k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor);

/*wczytanie obrazka o nazwie *name*/
SDL_Surface * init_pic(const char *name, window_scr& wind, int p = 0);
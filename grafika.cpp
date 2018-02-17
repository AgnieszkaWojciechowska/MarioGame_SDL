#pragma once
#include "grafika.h"

void init_graph(window_scr& wind, grafics& graph)
{
	//wczytanie obrazka
	wind.charset = init_pic("./cs8x8.bmp", wind, 2);
	graph.tlo = init_pic("./11.bmp", wind);
	graph.podloga = init_pic("./podloga.bmp", wind);
	graph.niebo = init_pic("./niebo.bmp", wind);
	graph.ico = init_pic("./ico_m.bmp", wind, 1);
	graph.ico_r1 = init_pic("./ico_r1.bmp", wind, 1);
	graph.ico_r2 = init_pic("./ico_r2.bmp", wind, 1);
	graph.ico_r3 = init_pic("./ico_r3.bmp", wind, 1);
	graph.ico_l1 = init_pic("./ico_l1.bmp", wind, 1);
	graph.ico_l2 = init_pic("./ico_l2.bmp", wind, 1);
	graph.ico_l3 = init_pic("./ico_l3.bmp", wind, 1);
	graph.ico_j = init_pic("./ico_j.bmp", wind, 1);
	graph.end = init_pic("./end_dot.bmp", wind, 3);
	graph.goom_1 = init_pic("./goombas1.bmp", wind, 1);
	graph.goom_2 = init_pic("./goombas2.bmp", wind, 1);
	graph.goom_3 = init_pic("./goombas3.bmp", wind, 1);
}

SDL_Surface * init_pic(const char *name, window_scr& wind, int p)
{
	SDL_Surface *surf;
	surf = SDL_LoadBMP(name);
	if (surf == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(wind.screen);
		SDL_DestroyTexture(wind.scrtex);
		SDL_DestroyWindow(wind.window);
		SDL_DestroyRenderer(wind.renderer);
		SDL_Quit();
	};
	if(p == 1)
		SDL_SetColorKey(surf, true, 0x00ff00);
	else if(p==2)
		SDL_SetColorKey(surf, true, 0x000000);
	else if (p==3)
		SDL_SetColorKey(surf, true, 0xff00ff);

	return surf;
}

void DrawString(SDL_Surface *screen, int x, int y, const char *text,
	SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y, int destx, int desty) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
};


void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

#pragma once
#include "info.h"

void game_infos(window_scr& wind, mario& mo, grafics& gr)
{ 
	wind.i = 0;
	// tekst informacyjny
	//DrawRectangle(wind.screen, INFOS_X, INFOS_Y, SCREEN_WIDTH - 2*INFOS_X, 36, mo.niebieski, mo.niebieski);
	sprintf(mo.text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", mo.worldTime, mo.fps);
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, INFOS_Y+(wind.i+=16), mo.text, wind.charset);
	sprintf(mo.text, "x = %i , y = %i, liczba zyc = %i",mo.x, mo.y, mo.life);
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, INFOS_Y + (wind.i += 16), mo.text, wind.charset);

	SDL_UpdateTexture(wind.scrtex, NULL, wind.screen->pixels, wind.screen->pitch);
	//		SDL_RenderClear(wind.renderer);
	SDL_RenderCopy(wind.renderer, wind.scrtex, NULL, NULL);
	SDL_RenderPresent(wind.renderer);
}

void save_info(window_scr& wind, mario& mo, grafics& gr, int ok)
{
	sprintf(mo.text, "zapisano pomyslnie");
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, INFOS_Y + (wind.i += 16), mo.text, wind.charset);

	SDL_UpdateTexture(wind.scrtex, NULL, wind.screen->pixels, wind.screen->pitch);
	//		SDL_RenderClear(wind.renderer);
	SDL_RenderCopy(wind.renderer, wind.scrtex, NULL, NULL);
	SDL_RenderPresent(wind.renderer);
}

void end_info(window_scr& wind, mario& mo)
{
	SDL_FillRect(wind.screen, NULL, mo.czarny);
	wind.i = 0;
	// tekst informacyjny
	DrawRectangle(wind.screen, MENU_X, MENU_Y, SCREEN_WIDTH - 2 * MENU_X, SCREEN_HEIGHT - 2 * MENU_Y, mo.niebieski, mo.niebieski);
	sprintf(mo.text, "Koniec gry!, czas trwania = %.1lf s  %.0lf klatek / s", mo.worldTime, mo.fps);
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, MENU_Y + (wind.i += 16), mo.text, wind.charset);
	sprintf(mo.text, "Nacisnij ESC by przejsc do menu...");
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, MENU_Y + (wind.i += 16), mo.text, wind.charset);

	SDL_UpdateTexture(wind.scrtex, NULL, wind.screen->pixels, wind.screen->pitch);
	//		SDL_RenderClear(wind.renderer);
	SDL_RenderCopy(wind.renderer, wind.scrtex, NULL, NULL);
	SDL_RenderPresent(wind.renderer);
}


void menu(window_scr& wind, mario& mo, grafics& gr)
{
	SDL_FillRect(wind.screen, NULL, mo.czarny);
	wind.i = 0;
	// tekst informacyjny
	DrawRectangle(wind.screen, MENU_X, MENU_Y, SCREEN_WIDTH - 2*MENU_X, SCREEN_HEIGHT-2*MENU_Y, mo.niebieski, mo.niebieski);
	sprintf(mo.text, "MENU");
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, MENU_Y+(wind.i+=48), mo.text, wind.charset);
	sprintf(mo.text, "n - nowa gra");
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, MENU_Y + (wind.i += 32), mo.text, wind.charset);
	sprintf(mo.text, "ESC - wyjscie");
	DrawString(wind.screen, wind.screen->w / 2 - strlen(mo.text) * 8 / 2, MENU_Y+(wind.i+=16), mo.text, wind.charset);

	SDL_UpdateTexture(wind.scrtex, NULL, wind.screen->pixels, wind.screen->pitch);
	//		SDL_RenderClear(wind.renderer);
	SDL_RenderCopy(wind.renderer, wind.scrtex, NULL, NULL);
	SDL_RenderPresent(wind.renderer);
}

void init_colors(window_scr& wind, mario& mo)
{
	mo.czarny = SDL_MapRGB(wind.screen->format, 0x00, 0x00, 0x00);
	mo.zielony = SDL_MapRGB(wind.screen->format, 0x00, 0xFF, 0x00);
	mo.czerwony = SDL_MapRGB(wind.screen->format, 0xFF, 0x00, 0x00);
	mo.niebieski = SDL_MapRGB(wind.screen->format, 0x11, 0x11, 0xCC);
}
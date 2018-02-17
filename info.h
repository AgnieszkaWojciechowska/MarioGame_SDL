#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef grafika
#include "grafika.h"
#endif
#ifndef window
#include "window.h"
#endif
#ifndef game
#include "game.h"
#endif
#define MENU_Y	100
#define MENU_X	8
#define INFOS_X	4
#define	INFOS_Y	4
/*wyswietlanie informacji*/
void game_infos(window_scr& wind, mario& mo, grafics& gr);
void init_colors(window_scr& wind, mario& mo);
void menu(window_scr& wind, mario& mo, grafics& gr);
void end_info(window_scr& wind, mario& mo);
void save_info(window_scr& wind, mario& mo, grafics& gr, int ok);

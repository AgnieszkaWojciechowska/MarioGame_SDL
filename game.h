#pragma once
#include "board.h"
//#include <windows.h>
#define GAME_WIDTH	600
#define GAME_HEIGHT	400
#define GAME_POS_X	20
#define GAME_POS_Y	60
#define PREDKOSC_POCZATKOWA_SKOKU_Y	5			//piksele na sekunde
const double PREDKOSC_POCZATKOWA_SKOKU = 5;
#define MARIO_ZYCIA		3
const double PRZYSPIESZENIE_MARIO = 40.0;				//piksele na sekunde
const double PRZYSPIESZENIE_ENEMY = 5.0;				//piksele na sekunde
const int ENEMY_WALK = 40;								//zasieg spaceru przeciwnika 13 = 1 kwadrat

struct mario
{
	
	int x;						//pozycja x mario
	int y;						//pozycja y mario
	int prawd;					//prawdopodobienstwo przesuniecia mario w prawo/lewo przy skoku-spadaniu
	int life;						//liczba zyc mario
	int end_lvl_x, end_lvl_y;		//okreslone miejsce gdzie mario ma dotrzec
	
	int quit;						//zmienna wjscia z gry = 1/0
	int quit_menu;					//zamkniecie okna
	int play;						//czy gra nadal trwa
	int t1, t2;						//zmienne do mierzenia czasu
	double delta, worldTime;		//do mierzenia czasu gry

	int ico_form;					//mario 0-stoi, 1-idzie w prawo, 2-idzie w lewo
	int form;						//do roznych animacji
	int post;						//zmiana animacji
	double walk_t1, walk_t2, is_walking_r, is_walking_l, walk_time;		//chodzenie mario

	int frames;						//klatki
	double fpsTimer, fps;		//do liczenia klatek

	char text[128];									//tekst wyswietlany na ekran
	int czarny, zielony, czerwony, niebieski;		//kolory

	int is_falling;
	double delta_s, jump_t1, jump_t2, jump_time, jump_height;	//zmienne do skakania mario
	int is_jumping, is_jump_xp, is_jump_xl;				//czy skacze w gore, czy skacze w prawo/lewo
	int speed;											//predkosc poczatkowa skakania
	int fall;											//czy mario spada podczas skakania
	int on_platform;										//czy jest na platformie

	int enemy_prawd;
	//int game_set = 0;

};
#ifndef info
#include "info.h"
#endif
void init_game(mario& mo, window_scr& wind, grafics& graph, board& lvl);
/*glowna funkcja sterujaca gra*/
void start_game(mario& mo, window_scr& wind, grafics& graph, board& lvl);
/*obsluga zdazen jestli jakies zaszly w grze*/
void key_controller(window_scr& wind, mario& mo, board& lvl, grafics& graph);
/*obsluga zdazen jestli jakies zaszly w menu*/
void key_controller_menu(window_scr& wind, mario& mo, board& lvl, grafics& graph);
/*licznik czasu*/
void count_time(mario& mo);
/*wyrysowanie gry na ekran*/
void draw_game(mario& mo, window_scr& wind, grafics& graph, board& lvl);

void fps_controller(mario& mo);


void end_game(mario& mo, window_scr& wind, board& lvl);
/*koniec czasu - utrata zycia*/
void lost_life(mario& mo, window_scr& wind, board& lvl);
/*koniec etapu - wczytanie nowego jesli jest lub koniec gry*/
void next_level(mario& mo, window_scr& wind, board& lvl);
void new_game(mario& mo, board& lvl);
/*poruszanie mario*/
void mario_move(mario& mo, board& lvl, grafics& graph, window_scr& wind);
/*spr czy mario stoi na platformie*/
void on_platform(board& lvl, mario& mo, grafics& graph);
/*zapis gry*/
int save_game(board& lvl, mario& mo);
/*wczytanie gry*/
void load_game(board& lvl, mario& mo);
/*poruszanie przeciwnikow*/
void enemy(mario& mo, window_scr& wind, grafics& graph, board& lvl);

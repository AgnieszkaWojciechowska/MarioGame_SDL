#define _CRT_SECURE_NO_WARNINGS
#ifndef grafika
#include "grafika.h"
#endif
#include<stdlib.h>
#define NUMBERS_AMOUNT_SIZE 4		//do sczytania rozmiaru planszy (max liczba cyfr rozmiaru)
const int ENEMYS_POSITIONS = 4;		//pozycja srodkowa_x, pozycja_srodkowa_y, aktualna pozycja_x, czy idzie w prawo(1) czy lewo(0)
const int PRZESUNIECIE_PLANSZY = 107;		//przesuniecie planszy na ekranie
struct board
{

	/*wczytywanie pliku etapu*/
	char** map_level;				//mapa wczytanego etapu z pliku
	int board_size_width;			//szerkosc wczytanej mapy etapu z pliku
	int board_size_height;			//wysokosc wczytanej mapy etapu z pliku

	FILE * str;						//uchwyt do wczytywanego pliku etapu
	char level[20];					//nazwa etapu do wczytania
	char level_save[20];			//nazwa etapu do zapisania
	int number_save;
	int number_of_level;
	long size;						//rozmiar wczytanego pliku
	char *bufor;					//bufor wczytanego pliku

	/*rysowanie na ekranie i kolizje*/
	char**collisions;				//mapa kolizji na ekranie
	int proc;						//zmienna do przesowania ekranu, gdy mario przesunie sie o cala swoja szerokosc (inaczej predkosc przesowania ekranu bylaby za duza)
	int z;							//z -> sluzy do przesowania widoku na ekranie (jest odpowiednio zwiekszane)
	int level_set;					//zmienna okreslajaca czy trzeba przerysowac widok ekranu etapu = 0/1
	int new_game;					//zmienna okreslajaca czy poczatek gry (do rysowania na ekranie i kolizji)

	int set_x;						//wczytana pozycja x mario z pliku
	int set_y;						//wczytana pozycja y mario z pliku
	double set_time;					//wczytany czas gry z pliku
	int set_lives;
	int **enemys;					//tablica z przeciwnikami
	int size_tab_enemy;	
	
};



//void update_board(window_scr& wind, mario& mo);
/*rysowanie planszy na ekranie*/
void draw_board(window_scr& wind, board& lvl, grafics& graph);
/*zakonczenie gry - zwolnienie pamieci*/
void close_board(board& lvl);
/*wczytywanie planszy*/
int init_board(board& lvl, int go);
/*wczytywanie etapu gry z pliku, go = 0 gdy wczytac chcemy zapisany plik*/
int load_level(board& lvl, int go);
/*ustawienie nazwy kolejnego pliku etapu*/
void level_name(board& lvl);

#pragma once
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include<math.h>
#include<stdio.h>
#include<string.h>

#include "window.h"
#include "grafika.h"
#include "game.h"
#include "info.h"



extern "C" {
//#ifdef BIT64
//#include"./sdl64/include/SDL.h"
//#include"./sdl64/include/SDL_main.h"
//#else
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"
//#endif
}





// main
#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char **argv) 
{
	mario mo;
	window_scr win;
	grafics graph;
	board lvl;

	init_game(mo, win, graph,lvl);
	
	return 0;
};

#include "board.h"

int init_board(board& lvl, int go)
{
	if (lvl.new_game)
	{
		lvl.number_of_level = 1;
		lvl.number_save = 1;
	}
	lvl.proc = 0;
	lvl.z = 0;			
	lvl.level_set = 0;
	if (!load_level(lvl,go))
		return 0;
	return 1;
}

void close_board(board& lvl)
{
	free(lvl.map_level);
}

/*void update_board(window_scr& wind, mario& mo)
{
	if (mo.x > 0)
	{

	}
}*/

void draw_board(window_scr& wind, board& lvl, grafics& graph)
{
	if (lvl.level_set && lvl.proc % graph.ico->w == 0 && lvl.z < lvl.board_size_width - (SCREEN_WIDTH / graph.podloga->w))
	{
		free(lvl.collisions);
		++lvl.z;
	}
	if ((lvl.level_set && lvl.proc % graph.ico->w == 0 && lvl.z < lvl.board_size_width - (SCREEN_WIDTH / graph.podloga->w)) 
		|| lvl.new_game)
	{
		lvl.collisions = (char**)malloc(sizeof(char*)*SCREEN_HEIGHT);
		for (int i = 0; i < SCREEN_HEIGHT; ++i)
		{
			lvl.collisions[i] = (char*)malloc(sizeof(char)*SCREEN_WIDTH);
			for (int j = 0; j < SCREEN_WIDTH; ++j)
				lvl.collisions[i][j] = '1';
		}
		lvl.new_game = 0;
		lvl.level_set = 0;
	}

	for (int m = 0, i = PRZESUNIECIE_PLANSZY; i < SCREEN_HEIGHT + 31 && m < lvl.board_size_height; i += graph.podloga->h, ++m)
	{
		for (int z = lvl.z, j = 0; j < SCREEN_WIDTH + 31 && z < lvl.board_size_width; j += graph.podloga->w, ++z)
		{
			switch (lvl.map_level[m][z])
			{
			case '0':
				//DrawSurface(wind.screen, graph.niebo, j, i, 0, 0);
				for (int g = i; g < i + graph.podloga->h && g < SCREEN_HEIGHT; ++g)
					for (int o = j; o < j + graph.podloga->w && o < SCREEN_WIDTH; ++o)
						lvl.collisions[g][o] = '0';
				break;
			case '1':
				DrawSurface(wind.screen, graph.podloga, j + 16, i - 16, 0, 0);
				for (int g = i; g < i + graph.podloga->h && g < SCREEN_HEIGHT; ++g)
				{
					for (int o = j; o < j + graph.podloga->w && o < SCREEN_WIDTH; ++o)
						lvl.collisions[g][o] = '1';

				}
				break;
			case '2':
				DrawSurface(wind.screen, graph.end, j + 16, i - 16, 0, 0);
				for (int g = i; g < i + graph.podloga->h && g < SCREEN_HEIGHT; ++g)
					for (int o = j; o < j + graph.podloga->w && o < SCREEN_WIDTH; ++o)
						lvl.collisions[g][o] = '2';
				break;
			}

			//desty += graph.podloga->h;
		}
	}
}

//wczytywanie tablicy kolizji poziomu gry
int load_level(board& lvl, int go)		//go=0 wczytaj zapisany
{
	if(go)
		level_name(lvl);
	lvl.str = fopen(lvl.level, "rb");
	if (lvl.str == NULL)
		return 0;
	fseek(lvl.str, 0, SEEK_END);
	lvl.size = ftell(lvl.str);
	rewind(lvl.str);

	lvl.bufor = (char*)malloc(sizeof(char)*lvl.size);
	if (lvl.bufor == NULL)
	{
		printf("\nBrak pamieci na wczytanie obrazka!");
		return 0;
	}

	if (fread(lvl.bufor, 1, lvl.size, lvl.str) != lvl.size)
	{
		printf("\nBlad pamieci!");
		return 0;
	}
	int z = 0, p = 0;
	char tab[NUMBERS_AMOUNT_SIZE + 1];		//+1 do '\0'
	while (lvl.bufor[z] != '\r' && p < NUMBERS_AMOUNT_SIZE)
		tab[p++] = lvl.bufor[z++];
	tab[p] = '\0';
	++(++z);
	lvl.board_size_width = atoi(tab);


	p = 0;
	while (lvl.bufor[z] != '\r' && p<NUMBERS_AMOUNT_SIZE)
		tab[p++] = lvl.bufor[z++];
	tab[p] = '\0';
	++(++z);
	lvl.board_size_height = atoi(tab);

	p = 0;
	while (lvl.bufor[z] != '\r' && p<NUMBERS_AMOUNT_SIZE)
		tab[p++] = lvl.bufor[z++];
	tab[p] = '\0';
	++(++z);
	lvl.set_x = atoi(tab);

	p = 0;
	while (lvl.bufor[z] != '\r' && p<NUMBERS_AMOUNT_SIZE)
		tab[p++] = lvl.bufor[z++];
	tab[p] = '\0';
	++(++z);
	lvl.set_y = atoi(tab);

	p = 0;
	while (lvl.bufor[z] != '\r' && p<NUMBERS_AMOUNT_SIZE)
		tab[p++] = lvl.bufor[z++];
	tab[p] = '\0';
	++(++z);
	lvl.set_time = atoi(tab);

	if (!go)
	{
		p = 0;
		while (lvl.bufor[z] != '\r' && p < NUMBERS_AMOUNT_SIZE)
			tab[p++] = lvl.bufor[z++];
		tab[p] = '\0';
		++(++z);
		lvl.set_lives = atoi(tab);

		p = 0;
		while (lvl.bufor[z] != '\r' && p < NUMBERS_AMOUNT_SIZE)
			tab[p++] = lvl.bufor[z++];
		tab[p] = '\0';
		++(++z);
		lvl.number_of_level = atoi(tab);
	}
	if (lvl.board_size_width <= 0 && lvl.board_size_height <= 0 && lvl.set_time > 0
		&& lvl.set_x > 0 && lvl.set_x < SCREEN_WIDTH
		&& lvl.set_y > 0 && lvl.set_y < SCREEN_HEIGHT)
	{
		printf("\nblad wczytywania lvl! Sprobuj jeszcze raz");
		return 0;
	}

	lvl.map_level = (char **)malloc(sizeof(char*)*lvl.board_size_height);
	for (int i = 0; i < lvl.board_size_height; ++i)
	{
		lvl.map_level[i] = (char*)malloc(sizeof(char)*lvl.board_size_width);
		for (int j = 0; j < lvl.board_size_width; ++j, ++z)
			lvl.map_level[i][j] = lvl.bufor[z];
		++(++z);							//podwojna inkrementacja poniewaz pomijamy znak enter
	}

	p = 0;
	while (lvl.bufor[z] != '\r' && p < NUMBERS_AMOUNT_SIZE)
		tab[p++] = lvl.bufor[z++];
	tab[p] = '\0';
	++(++z);
	lvl.size_tab_enemy = atoi(tab);

	lvl.enemys = (int **)malloc(sizeof(int *)*lvl.size_tab_enemy);
	for (int i = 0; i < lvl.size_tab_enemy; ++i)
	{
		lvl.enemys[i] = (int*)malloc(sizeof(int)*ENEMYS_POSITIONS);
		for (int j = 0; j < ENEMYS_POSITIONS; ++j)
		{
			p = 0;
			while (lvl.bufor[z] != '\r' && p < NUMBERS_AMOUNT_SIZE)
				tab[p++] = lvl.bufor[z++];
			tab[p] = '\0';
			++(++z);
			lvl.enemys[i][j] = atoi(tab);
		}
	}




	free(lvl.bufor);
	fclose(lvl.str);
	return 1;
}

void level_name(board& lvl)
{
	sprintf(lvl.level, "level%.i.txt", lvl.number_of_level++);
}


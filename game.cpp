#pragma once
#include "game.h"

void init_game(mario& mo, window_scr& wind, grafics& graph, board& lvl)
{
	//tryb okna
	init_window(wind);
	init_colors(wind, mo);
	init_graph(wind, graph);
	mo.quit_menu = 0;

	while (!mo.quit_menu)
	{
		menu(wind, mo, graph);
		key_controller_menu(wind, mo, lvl, graph);
		while (!mo.quit)
		{
			start_game(mo, wind, graph, lvl);
			while (SDL_PollEvent(&wind.event))
			{
				switch (wind.event.type)
				{
				case SDL_KEYDOWN:
					switch (wind.event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						mo.quit = 1;
						break;
					}
				case SDL_QUIT:
					mo.quit = 1;
					break;
				}
			}
		}
	}
	quit_window(wind);
}

void new_game(mario& mo, board& lvl)
{
	lvl.new_game = 1;
	mo.t1 = SDL_GetTicks();
	mo.frames = 0;
	mo.prawd = 0;
	mo.fpsTimer = 0;
	mo.fps = 0;
	mo.fall = 0;
	mo.speed = PREDKOSC_POCZATKOWA_SKOKU_Y;
	mo.delta_s = 0;
	mo.quit = 0;
	mo.play = 1;
	mo.life = MARIO_ZYCIA;
	mo.jump_height = 0;
	mo.jump_time = 0;
	mo.jump_height = 0;
	mo.is_jumping = 0;
	mo.is_jump_xp = 0;
	mo.is_jump_xl = 0;
	if (!init_board(lvl,1))
		mo.quit = 1;
	mo.is_walking_r = 0;
	mo.is_walking_l = 0;
	mo.ico_form = 0;
	mo.x = lvl.set_x;
	mo.y = lvl.set_y;
	mo.worldTime = lvl.set_time;	
	mo.is_falling = 0;
	mo.form = 0;
	mo.enemy_prawd = 0;
}

void start_game(mario& mo, window_scr& wind,  grafics& graph, board& lvl)
{
	while (!mo.quit && mo.play)
	{
		count_time(mo);
		
		
		draw_game(mo, wind, graph,lvl);
		

		fps_controller(mo);
		
		game_infos(wind, mo, graph);						//tekst info
		key_controller(wind, mo, lvl, graph);							// obs³uga zdarzeñ (o ile jakieœ zasz³y)
		mo.frames++;
		
		mario_move(mo, lvl, graph,wind);
		next_level(mo, wind, lvl);
		lost_life(mo, wind, lvl);
		
	}
}

void lost_life(mario& mo, window_scr& wind, board& lvl)
{
	if (mo.worldTime == 0 || mo.y >= SCREEN_HEIGHT)
	{
		--mo.life;
		--lvl.number_of_level;
		init_board(lvl,1);
		mo.x = lvl.set_x;
		mo.y = lvl.set_y;
		mo.worldTime = lvl.set_time;
		if (mo.life == 0)
			end_game(mo, wind, lvl);
	}
	for (int i = 0; i < lvl.size_tab_enemy; ++i)
	{
		if (mo.x+16 == lvl.enemys[i][2] && mo.y == lvl.enemys[i][1] * 31 + PRZESUNIECIE_PLANSZY)
		{
			--mo.life;
			--lvl.number_of_level;
			init_board(lvl, 1);
			mo.x = lvl.set_x;
			mo.y = lvl.set_y;
			mo.worldTime = lvl.set_time;
			if (mo.life == 0)
				end_game(mo, wind, lvl);
		}
	}
}

void end_game(mario& mo, window_scr& wind, board& lvl)
{
	end_info(wind, mo);
	mo.play = 0;
	close_board(lvl);
	while (SDL_PollEvent(&wind.event))
	{
		switch (wind.event.type)
		{
		case SDL_KEYDOWN:
			switch (wind.event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				mo.quit = 1;
				break;
			}
		case SDL_QUIT:
			mo.quit = 1;
			break;
		}
	}

}

void key_controller(window_scr& wind, mario& mo, board& lvl, grafics& graph)
{
	on_platform(lvl, mo, graph);
	while (SDL_PollEvent(&wind.event))
	{
		switch (wind.event.type)
		{
		case SDL_KEYDOWN:
			switch (wind.event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				end_game(mo, wind, lvl);
				mo.quit = 1;
				break;
			case SDLK_n:
				new_game(mo, lvl);
				break;
			case SDLK_s:
				save_info(wind,mo,graph, save_game(lvl, mo));
				break;
			case SDLK_l:
				load_game(lvl, mo);
				break;
			case SDLK_RIGHT:
				mo.ico_form = 1;
				if (mo.is_jumping)
				{
					mo.is_jump_xp = 1;
					mo.is_jump_xl = 0;
				}
				else 
				{
					if (!mo.is_walking_r)
					{
						mo.walk_t1 = SDL_GetTicks();
						mo.is_walking_r = 1;
					}
					mo.walk_t2 = SDL_GetTicks();;
					mo.walk_time= (mo.walk_t2 - mo.walk_t1) * 0.001;

					int x = (PRZYSPIESZENIE_MARIO*mo.walk_time*mo.walk_time) / 2;
					if (x == 0)
						x = 4;
					if ((mo.x + graph.ico->w + x) < SCREEN_WIDTH && lvl.collisions[mo.y][(mo.x + graph.ico->w+1)] != '1')
						mo.x += x;
				}
				break;
			case SDLK_LEFT:
				mo.ico_form = 2;
				if (mo.is_jumping)
				{
					mo.is_jump_xl = 1;
					mo.is_jump_xp = 0;
				}
				else 
				{
					if (!mo.is_walking_l)
					{
						mo.walk_t1 = SDL_GetTicks();
						mo.is_walking_l = 1;
					}
					mo.walk_t2 = SDL_GetTicks();;
					mo.walk_time = (mo.walk_t2 - mo.walk_t1) * 0.001;
					int x = (PRZYSPIESZENIE_MARIO*mo.walk_time*mo.walk_time) / 2;
					if (x == 0)
						x = 4;
					if (mo.x - x> 0 && lvl.collisions[mo.y][mo.x - 1] != '1' )
						mo.x -= x;
				}
				break;
			case SDLK_UP:
				mo.ico_form = 3;
				if (mo.is_jumping == 0)
					mo.jump_t1 = SDL_GetTicks();
				else if (mo.speed < 8 && !mo.fall)
					mo.speed += 1;
				mo.is_jumping = 1;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (wind.event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				mo.is_walking_r = 0;
				if (mo.ico_form == 1)
					mo.ico_form = 0;
				break;
			case SDLK_LEFT:
				if (mo.ico_form == 2)
					mo.ico_form = 0;
				mo.is_walking_l = 0;
				break;
			case SDLK_UP:
				
				break;
			}
			break;
			
		case SDL_QUIT:
			mo.quit = 1;
			break;
		}

	};
	if (mo.ico_form == 3 && !mo.is_jumping)
		mo.ico_form = 0;
	if (mo.is_jumping)
		mo.ico_form = 3;
}

void count_time(mario& mo)
{
	mo.t2 = SDL_GetTicks();

	// w tym momencie t2-t1 to czas w milisekundach,
	// jaki uplyna³ od ostatniego narysowania ekranu
	// delta to ten sam czas w sekundach
	mo.delta = (mo.t2 - mo.t1) * 0.001;
	mo.t1 = mo.t2;

	mo.worldTime -= mo.delta;
	if (mo.worldTime < 0)
		mo.worldTime = 0;	
}

void draw_game(mario& mo, window_scr& wind, grafics& graph, board& lvl)
{
	SDL_FillRect(wind.screen, NULL, mo.niebieski);

	//DrawSurface(wind.screen, graph.tlo,-SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0,0);
	//DrawRectangle(wind.screen, GAME_POS_X, GAME_POS_Y, GAME_WIDTH, GAME_HEIGHT, mo.czerwony, mo.niebieski);
	
	draw_board(wind, lvl, graph);
	if (mo.x > SCREEN_WIDTH / 2 && ++lvl.proc % graph.ico->w == 0)
	{
		if(lvl.z < lvl.board_size_width - (SCREEN_WIDTH / graph.podloga->w)-16)
			mo.x = SCREEN_WIDTH / 2;
		//mo.game_set = 1;
		lvl.level_set = 1;
	}
	if (mo.ico_form == 1)
	{
		if(++mo.post %20 == 0)
			++mo.form;
		if(mo.form == 0)
			DrawSurface(wind.screen, graph.ico_r1, mo.x + 16, mo.y - 16, 0, 0);
		else if(mo.form == 1)
			DrawSurface(wind.screen, graph.ico_r2, mo.x + 16, mo.y - 16, 0, 0);
		else if (mo.form == 2)
		{
			DrawSurface(wind.screen, graph.ico_r3, mo.x + 16, mo.y - 16, 0, 0);
			if (mo.post % 20 == 0)
			{
				mo.form = 0;
				mo.post = 0;
			}
		}
		
	}
	else if (mo.ico_form == 2)
	{
		if (++mo.post % 20 == 0)
			++mo.form;
		if (mo.form == 0)
			DrawSurface(wind.screen, graph.ico_l1, mo.x + 16, mo.y - 16, 0, 0);
		else if (mo.form == 1)
			DrawSurface(wind.screen, graph.ico_l2, mo.x + 16, mo.y - 16, 0, 0);
		else if (mo.form == 2)
		{
			DrawSurface(wind.screen, graph.ico_l3, mo.x + 16, mo.y - 16, 0, 0);
			if (mo.post % 20 == 0)
			{
				mo.form = 0;
				mo.post = 0;
			}
		}

	}
	else if (mo.ico_form == 3)
	{
		DrawSurface(wind.screen, graph.ico_j, mo.x + 16, mo.y - 16, 0, 0);
		mo.form = 0;
	}
	else
	{
		DrawSurface(wind.screen, graph.ico, mo.x + 16, mo.y - 16, 0, 0);
		mo.form = 0;
	}
	//		DrawScreen(screen, plane, ship, charset, worldTime, delta, vertSpeed);

	// naniesienie wyniku rysowania na rzeczywisty ekran
	//		SDL_Flip(screen);
	enemy(mo, wind, graph, lvl);

}

void enemy(mario& mo, window_scr& wind, grafics& graph, board& lvl)
{
	for (int i = 0; i < lvl.size_tab_enemy; ++i)
	{
		if (lvl.enemys[i][0] >= lvl.z && lvl.enemys[i][0] <= lvl.z + (SCREEN_WIDTH / graph.podloga->w))
		{
			if (lvl.enemys[i][2] >= (lvl.enemys[i][0]*31-lvl.z*16) + ENEMY_WALK && lvl.enemys[i][3] == 1)	//lvl.enemys[i][2] jest w notacji x ekranu, reszta podlug planszy w pliku
			{
				lvl.enemys[i][3] = 0;
				mo.enemy_prawd = 0;
			}
			else if (lvl.enemys[i][2] <= (lvl.enemys[i][0] * 31 -lvl.z*16) - ENEMY_WALK && lvl.enemys[i][3] == 0)
				lvl.enemys[i][3] = 1;

			if (lvl.enemys[i][3])
			{
				if (++mo.enemy_prawd % 7 == 0)
				{
					if(lvl.collisions[lvl.enemys[i][1] * 31 + PRZESUNIECIE_PLANSZY][lvl.enemys[i][2]-lvl.z*16+1+31] != '1')
						++lvl.enemys[i][2];
					else
					{
						lvl.enemys[i][3] = 0;
						mo.enemy_prawd = 0;
					}
				}
				DrawSurface(wind.screen, graph.goom_1, lvl.enemys[i][2]-lvl.z*16 + 16, lvl.enemys[i][1]*31+PRZESUNIECIE_PLANSZY - 16, 0, 0);
			}
			else
			{
				if (++mo.enemy_prawd % 7 == 0)
				{
					if (lvl.collisions[lvl.enemys[i][1] * 31 + PRZESUNIECIE_PLANSZY][lvl.enemys[i][2]-lvl.z*16 - 1] != '1')
						--lvl.enemys[i][2];
					else
						lvl.enemys[i][3] = 1;
				}
				DrawSurface(wind.screen, graph.goom_1, lvl.enemys[i][2]-lvl.z*16 + 16, lvl.enemys[i][1]*31+PRZESUNIECIE_PLANSZY - 16, 0, 0);
			}
		}
	}
}

void fps_controller(mario& mo)
{
	mo.fpsTimer += mo.delta;
	if (mo.fpsTimer > 0.5) {
		mo.fps = mo.frames * 2;
		mo.frames = 0;
		mo.fpsTimer -= 0.5;
	};
}


void mario_move(mario& mo, board& lvl, grafics& graph, window_scr& wind)
{
	if (mo.is_jumping || mo.is_falling)
	{
		_sleep(8);
		//for (int i = 0; i < 70; ++i)
		//{
			
			mo.jump_t2 = SDL_GetTicks();

			// w tym momencie t2-t1 to czas w milisekundach,
			// jaki uplyna³ od ostatniego narysowania ekranu
			// delta to ten sam czas w sekundach
			mo.delta_s = (mo.jump_t2 - mo.jump_t1) * 0.001;


			mo.jump_time = mo.delta_s;
			double max_t = (2 * 130 * sin(0.3) / 9.8);
			/*if (mo.jump_time >= ((max_t / 2) - 2) && mo.jump_time >= ((max_t / 2)))
				mo.jump_t2 = mo.jump_time + mo.jump_t1;*/
			//if (mo.jump_time < max_t)
			
			if (mo.is_jumping)
			{
				int where_jump = mo.jump_height;
				mo.jump_height = -(((mo.speed * sin(1.45))*mo.jump_time - (9.8*mo.jump_time*mo.jump_time) / 2));
				if (mo.jump_height - where_jump > 0)		//wieksze bo y rosnie w dol
					mo.fall = 1;
				int y = (mo.jump_height - where_jump);
				if (mo.y >= 0 && mo.y + (mo.jump_height - where_jump) < SCREEN_HEIGHT &&
					lvl.collisions[mo.y + y][mo.x + graph.ico->w / 2] != '1')
					mo.y += (mo.jump_height - where_jump);
				else
				{
					mo.is_jumping = 0;
					mo.jump_t1 = SDL_GetTicks();
					mo.is_falling = 1;
				}
			}
			if (mo.is_falling)
			{
				double where_jump = mo.jump_height;
				mo.jump_height += (9.8*mo.jump_time*mo.jump_time) / 2;
				mo.y += mo.jump_height - where_jump;
				lost_life(mo, wind, lvl);
			}
			
			
			//mo.y = mo.jump_height;
			if(mo.is_jump_xp)
			{
				if (++mo.prawd % 5 && (mo.x + graph.ico->w + 1) < SCREEN_WIDTH && 
					lvl.collisions[mo.y][(mo.x + graph.ico->w + 1)] != '1')
					++mo.x;
			}
			else if(mo.is_jump_xl && (mo.x - 1) >0 && lvl.collisions[mo.y][(mo.x - 1)] != '1')
			{
				if (++mo.prawd % 5)
					--mo.x;
			}
			
			on_platform(lvl, mo, graph);
			if(mo.on_platform)
			{
				mo.is_jumping = 0;
				mo.is_falling = 0;
			}
	}
	if(mo.on_platform)
	{
		mo.prawd = 0;
		mo.jump_height = 0;
		mo.is_jump_xl = 0;
		mo.is_jump_xp = 0;
		mo.speed = PREDKOSC_POCZATKOWA_SKOKU_Y;
		mo.fall = 0;
		
	}
}

void on_platform(board& lvl, mario& mo, grafics& graph)
{
	if (mo.y>=0 && mo.y + graph.ico->h < SCREEN_HEIGHT && mo.x>=0 && mo.x+1 < SCREEN_WIDTH && 
		lvl.collisions[mo.y+graph.podloga->h][mo.x+graph.podloga->w/2] == '1')
		mo.on_platform = 1;
	else
	{
		if (!mo.is_jumping)
		{
			if (mo.is_falling == 0)
				mo.jump_t1 = SDL_GetTicks();
			mo.is_falling = 1;
		}
		mo.on_platform = 0;
		
	}
}

void key_controller_menu(window_scr& wind, mario& mo, board& lvl, grafics& graph)
{
	while (SDL_PollEvent(&wind.event))
	{
		switch (wind.event.type)
		{
		case SDL_KEYDOWN:
			switch (wind.event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				mo.quit_menu = 1;
				break;
			case SDLK_n:
				new_game(mo, lvl);
				break;
			}
			break;
		

		case SDL_QUIT:
			mo.quit_menu = 1;
			break;
		}

	};
}

void next_level(mario& mo, window_scr& wind, board& lvl)
{
	if (mo.y + 31 <= SCREEN_HEIGHT && mo.x+17 <SCREEN_WIDTH && mo.x >=0 && mo.y >= 0 && lvl.collisions[mo.y+16][mo.x+17] == '2')
	{
		if (!init_board(lvl,1))
			end_game(mo,wind,lvl);
		mo.x = lvl.set_x;
		mo.y = lvl.set_y;
		mo.worldTime = lvl.set_time;
	}

}

void load_game(board& lvl, mario& mo)
{
	if (lvl.number_save - 1 > 0)
	{
		sprintf(lvl.level, "save%.i.txt", lvl.number_save-1);
		--lvl.number_of_level;
		init_board(lvl,0);
		mo.x = lvl.set_x;
		mo.y = lvl.set_y;
		mo.worldTime = lvl.set_time;
	}
}

int save_game(board& lvl, mario& mo)
{
	sprintf(lvl.level_save, "save%.i.txt", lvl.number_save++);
	lvl.str = fopen(lvl.level_save, "w+");

	fprintf(lvl.str, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n", lvl.board_size_width, lvl.board_size_height, mo.x, mo.y, (int)mo.worldTime, mo.life, lvl.number_of_level);

	for (int i = 0; i < lvl.board_size_height; ++i)
	{
		for (int j = 0; j < lvl.board_size_width; ++j)

			fprintf(lvl.str, "%c", lvl.map_level[i][j]);

		fprintf(lvl.str, "\n");
	}
	fprintf(lvl.str, "%d\n", 0);

	fclose(lvl.str);
	return 1;
}
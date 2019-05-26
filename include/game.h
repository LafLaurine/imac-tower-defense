#ifndef GAME_H
#define GAME_H
#pragma once
#include "monster.h"

typedef struct game{
	int money;
	int monster_alive;
	int nb_lists_send;
	int nb_lists_killed; 
	int time;
	int over;
	int wave;
}Game;

Game* new_game();
int game_update(Game* game, Monster* m_alive);
int player_money_update(Game* game, int cost);
void game_end(Game* game);

#endif

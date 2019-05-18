#ifndef GAME_H
#define GAME_H
#include "monster.h"

typedef struct game{
	int money;
	int monster_alive;
	int nb_lists_send;
	int nb_lists_killed; 
	int time;
	int over;
}Game;

Game* new_game();
int game_update(Game* game, Monster* m_alive);
int player_money_update(Game* game, int cost);
void game_end(Game* game);
int click_tour_delete(List_Tower* list_tower, Tower* current, Game* game);

#endif

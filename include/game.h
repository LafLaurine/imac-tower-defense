#ifndef PLAYER_H
#define PLAYER_H
#include "monster.h"

typedef struct game{
	int money;
	int player_lvl;
	int monster_alive;
	int player_life;
	int time;

}Game;

Game* new_game();
int game_update(Game* game, Monster* m_alive);
void update_player();
int player_update(Game* game);
int player_money_update(Game* game, int cost);
int player_life(Game* game);
void game_end(Game* game);

#endif

#ifndef GAME_H
#define GAME_H
#include "monster.h"

typedef struct game{
	int money;
	int nb_lists_send;
	int start;
	int win;
	int pause;
	int over;
}Game;

// Create new game
Game* new_game();
// Game update
int game_update(Game* game, Monster* m_alive);
// Update money UP
int player_money_up_update(Game* game, int cost);
// Update money DOWN
int player_money_down_update(Game* game, int cost);
// End game
void game_end(Game* game);

#endif
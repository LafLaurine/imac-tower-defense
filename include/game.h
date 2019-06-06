#ifndef GAME_H
#define GAME_H
#include "monster.h"

typedef struct game{
	int money;
	int start;
	int win;
	int pause;
	int over;
}Game;

// Create new game
Game* new_game();
// Update money UP
int player_money_up_update(Game* game, int cost);
// Update money DOWN
int player_money_down_update(Game* game, int cost);
// End game
void game_end(Game* game);

#endif
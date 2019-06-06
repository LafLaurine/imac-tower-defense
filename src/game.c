#include "../include/game.h"

Game* new_game() {
	Game* n_game = malloc(sizeof(Game));

	if(n_game != NULL) {
		n_game->money = 500; // Player starts with 150 medics
		n_game->nb_lists_send = 0;
		n_game->pause = 0;
		n_game->start = 0;
		n_game->win = 0;
		n_game->over = 0;

	} else {
		printf("Game cannot start\n");
		exit(EXIT_FAILURE);
	}
	
	return n_game;
}

int player_money_down_update(Game* game, int cost) {
	// If game has began
	if(game != NULL) {
		//player lost money
		game->money -= cost;

	} else {
		printf("Money won't update\n");
		return 0;
	}

	return 1;
}

int player_money_up_update(Game* game, int cost) {
	// If game has began
	if(game != NULL) {
		//player won money
		game->money += cost;
		
	} else {
		printf("Money won't update\n");
		return 0;
	}
	
	return 1;
}

//end of the game, must free
void game_end(Game* game) {
	if (game != NULL) {
		free(game);
	}
}
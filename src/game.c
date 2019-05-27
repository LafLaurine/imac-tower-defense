#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/game.h"

Game* new_game() {
	Game* n_game = malloc(sizeof(Game));
	if(n_game != NULL) {
		//player start with 500
		n_game->money = 500;
		n_game->monster_alive = 0;
		n_game->nb_lists_send = 0;
		n_game->nb_lists_killed = 0; 
		n_game->time = 0;
		n_game->wave = 0;
		n_game->over = 0;
	}
	else {
		fprintf(stderr, "Game cannot start\n");
		return NULL;
	}
	
	return n_game;
}

int player_money_up_update(Game* game, int cost) {

	//Si le jeu a commencé
	if(game != NULL) {
	
		game->money -= cost;
		
	}
	else {
		fprintf(stderr, "Money won't update\n");
		return 0;
	}
	
	return 1;
}

int player_money_down_update(Game* game, int cost) {
	//Si le jeu a commencé
	if(game != NULL) {
	
		game->money += cost;
		
	}
	else {
		fprintf(stderr, "Money won't update\n");
		return 0;
	}
	
	return 1;
}

// Affichage du budget
void display_budget() {
	
}


void game_end(Game* game) {
	if (game != NULL) {
		free(game);
	}
}
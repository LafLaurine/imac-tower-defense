#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/game.h"

Game* new_game() {
	Game* n_game = malloc(sizeof(Game));
	if(n_game != NULL) {
		//player start with 100
		n_game->money = 100;
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

//Monstres première vague = +5 unité d'argent, a chaque nouvelle vague, monstre rapportent + de money
int player_money_update(Game* game, int cost) {

	//Si l'interface a été alloué
	if(game != NULL) {
	
		game->money -= cost;
		
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
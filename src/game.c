#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/game.h"

Game* new_game() {
	Game* n_game = malloc(sizeof(Game));
	if(n_game != NULL) {
		//player start with 100
		n_game->money = 100;
		n_game->player_lvl = 0;
		n_game->monster_alive = 0;
		//player got 3 lifes
		n_game->player_life = 3;
		n_game->time = 0;
	}
	else {
		fprintf(stderr, "Game cannot start\n");
		return NULL;
	}
	
	return n_game;
}

int game_update(Game* game, Monster* m_alive) {
	if(game != NULL) {
		if(m_alive != NULL) {
			if(m_alive->pv == 0) {
				game->money += m_alive->money;
			}
			game->monster_alive++;
		}
		else {
			fprintf(stderr, "Monster are not there\n");
			return 0;
		}

	}
	else {
		fprintf(stderr, "Monster won't update\n");
		return 0;
	}	

	return 1;

}

int player_update(Game* game) {
	if(game != NULL) {
		game->player_lvl++;
		//win 100 credirs if update lvl
		game->money += 100;
	}
	else {
		fprintf(stderr, "Player won't update\n");
		return 0;
	}
	
	return 1;
}

//when player buy something
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

int player_life(Game* game) {

	//Si l'interface a été alloué
	if(game != NULL) {
	
		game->player_life --;
		
	}
	else {
		fprintf(stderr, "Life won't change\n");
		return 0;
	}
	
	return 1;
}

void update_player(Game *game, int cost) {
	player_update(game);
	player_money_update(game,cost);
	player_life(game);
}

void game_end(Game* game) {
	if (game != NULL) {
		free(game);
	}
}

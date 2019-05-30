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
		n_game->wave = 0;
		n_game->pause = 0;
		n_game->start = 0;
		n_game->win = 0;
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
void display_budget(Game *player) {		
		int money = player->money;

		//Alloue de la mémoire pour une chaine de caractère
		char* machaine = malloc(20*sizeof(char));

		//Si la chaine de caracteres à bien été alloué
		if(machaine != NULL) {
					glColor4f(0,0,0, 0.5);
					glBegin(GL_QUADS);
						glVertex2f(195,422);
						glVertex2f(325,422);
						glVertex2f(325,445);
						glVertex2f(195,445);
					glEnd();
					glColor4f(255,255,255, 1);
					//Convertie un int en un string
					sprintf(machaine,"%d",money);
					vBitmapOutput(205, 440,  "Money :",GLUT_BITMAP_HELVETICA_18);				
					vBitmapOutput(280, 440,  machaine,GLUT_BITMAP_HELVETICA_18);			
		} else {
		fprintf(stderr, "Erreur cette tour n'existe pas\n");
	}	
}


void game_end(Game* game) {
	if (game != NULL) {
		free(game);
	}
}
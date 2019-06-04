#include "../include/game.h"

Game* new_game() {
	Game* n_game = malloc(sizeof(Game));

	if(n_game != NULL) {
		n_game->money = 500; // Player starts with 500
		n_game->monster_alive = 0;
		n_game->nb_lists_send = 0;
		n_game->nb_lists_killed = 0; 
		n_game->wave = 0;
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
		game->money += cost;
		
	} else {
		printf("Money won't update\n");
		return 0;
	}
	
	return 1;
}

void display_budget(Game *player) {		
		int money = player->money;

		// Allocate memory for string
		char* s_money = malloc(20*sizeof(char));

		// If memory was allocate
		if(s_money != NULL) {
					glColor4f(0,0,0, 0.5);
					glBegin(GL_QUADS);
						glVertex2f(195,422);
						glVertex2f(325,422);
						glVertex2f(325,445);
						glVertex2f(195,445);
					glEnd();
					glColor4f(255,255,255, 1);
					// Convert int to string
					sprintf(s_money, "%d", money);
					vBitmapOutput(205, 440,  "Money :",GLUT_BITMAP_HELVETICA_18);				
					vBitmapOutput(280, 440,  s_money,GLUT_BITMAP_HELVETICA_18);			
		} else {
			printf("String money memory not allocated\n");
	}	
}

void game_end(Game* game) {
	if (game != NULL) {
		free(game);
	}
}
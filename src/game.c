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
		n_game->over = 0;
	}
	else {
		fprintf(stderr, "Game cannot start\n");
		return NULL;
	}
	
	return n_game;
}



//when player buy something
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

void game_end(Game* game) {
	if (game != NULL) {
		free(game);
	}
}
/*
int add_tower_to_game(List_Tower* list_tower, TowerType type, Game* game) {

	//Vérifie si les elements ont été alloué
	if(list_tower != NULL && game != NULL) {
		//Vérifie qu'on clique sur la bonne touche
		SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
        	if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_b))
            {
                type = BLUE; 
            }
            else if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_y))
            {
                type = YELLOW; 
                break;
            }
            else if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_r))
            {
                type = ROCKET; 
                break;
            }
             else if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_l))
            {
                type = LASER; 
                break;
            }
        }

		//Vérifie qu'il y a un type, sinon pas de clique sur l'un des boutons
		if(strcmp("None", type) != 0) {

			//Pointeur temporaire pour parcourir la liste
			List_Tower* tmp = list_tower->t_first;
	
			//Parcours la liste
			while(tmp != NULL) {
				tmp = tmp->t_next;
			}

			//S'il le joueur a assez d'argent
			if((game->money) >= tmp->cost) {
				//Ajoute une tour sur map 
				?????
				//Met a jour l'agent
				player_update_money(game, tmp->cost);
				return 1;
			}
		}
		
	}
	else {
		fprintf(stderr, "Error allocate\n");
		exit(EXIT_FAILURE);
	}

	return 0;

}*/

//supprimer tour
int click_tour_delete(List_Tower* list_tower, Tower* current, Game* game) {

	if(list_tower != NULL) {

		if(current != NULL) {
				game->money += current->cost;
				list_tower = delete_from_position(list_tower, current);
		}
		else {
			fprintf(stderr, "Tower doesn't exist\n");
			exit(EXIT_FAILURE);
		}

	}
	else {
		fprintf(stderr, "Tower list fail\n");
		exit(EXIT_FAILURE);
	}

	return 1;

}


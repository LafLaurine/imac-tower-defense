#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../include/tower.h"

List_Tower* new_tower_list() {
	List_Tower *list_tower = malloc(sizeof(List_Tower));
	if (list_tower != NULL) {
		list_tower->length = 0;
		list_tower->t_first = NULL;
		list_tower->t_last = NULL;
	}
	else {
		printf("%s\n", "Not enough memory");
		return NULL;
	}
	return list_tower;
}

Tower* create_tower(TowerType type, float x, float y, Node* head, List_Tower* l_tower, int money){
	Tower* t = malloc(sizeof(Tower)); 
	if(t != NULL) {
		t->type = type; //type
		t->x = x; //coordonnee x
		t->y = y; //coordonnee y
		t->node_prev = head; //Pointeur vers le premier noeud
		t->node_next = head->next; //Pointeur vers le second noeud
		t->node_next = NULL; 
		t->t_next = NULL;
		t->t_prev = NULL;

		if(type == LASER) {
			t->rate = 10; //La vitesse de tir
			t->power = 5; //puissance de l'attaque
			t->range = 50; //portee
			t->cost = 10; //prix
		}
		else if(type == ROCKET) {
			t->rate = 15;
			t->power = 15;
			t->range = 50;
			t->cost = 20;
		}
		else if(type == YELLOW) {
			t->rate = 20;
			t->power = 5;
			t->range = 200;
			t->cost = 50;
		}
		else if(type == BLUE) {
			t->rate = 50;
			t->power = 10;
			t->range = 250;
			t->cost = 100;
		}
		add_tower_list(t, l_tower);
		printf("%s\n", "New tower");
		if(money >= t->cost) {
			return t;
		}
		else {
			printf("Tu n'as pas assez d'argent");
			return NULL;
		}
	}
	else {
		printf("%s\n", "Not enough memory for tower");
		exit(EXIT_FAILURE);
	}
}

void add_tower_list(Tower* t, List_Tower* list_tower){
	if (list_tower != NULL) {
		if (list_tower->t_last == NULL) {
				// Pointe la tête de la liste sur le nouveau monstre
				list_tower->t_first = t; 
				t->t_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				t->t_prev = list_tower->t_last; 
				list_tower->t_last->t_next = t;  
			}
			
			// Pointe la fin de la liste sur le nouveau monstre
			list_tower->t_last = t; 

			// On augmente de 1 la taille de la liste
			list_tower->length++; 
		}
	else {
		printf("%s\n", "Fail to add to list tower");
	}
}


Tower* click_tower(List_Tower* p_ltower, float x, float y) {
	
	//Vérifie que la liste de tours existe
	if(p_ltower != NULL) {

		//Tour temporaire pour parcourir la liste de tour
		Tower* p_tmp = p_ltower->t_last;
		
		while(p_tmp != NULL) {

			//Si on a cliqué sur une tour
			if(x <= (p_tmp->x + 50) && x >= (p_tmp->x - 50) && y <= (p_tmp->y + 50) && y >= (p_tmp->y - 50)) {
				return p_tmp;	
			}

			p_tmp = p_tmp->t_prev;

		}
	}
	else {
		fprintf(stderr, "Erreur :wrong liste tour\n");
		return NULL;
	}

	return NULL;

}

//delete tower from list and return list of tower
List_Tower* delete_from_position(List_Tower* list_tower, Tower* current) {
	if (list_tower != NULL) {

		if(current != NULL) {

			//Si c'est la dernière tour de la liste
			if (current->t_next == NULL) {
				
				//Pointe la fin de la liste sur la tour précédente
				list_tower->t_last = current->t_prev;

				if(list_tower->t_last != NULL) {
					//Lien de la dernière tour vers la tour suivante est NULL
					list_tower->t_last->t_next = NULL;
				}
				else
					list_tower->t_first = NULL;
					
			}
		
			//Si c'est la première de la liste
			else if (current->t_prev == NULL) {
				list_tower->t_first = current->t_next;

				if(list_tower->t_first != NULL) {
			 		list_tower->t_first->t_prev = NULL;
				}
				else
					list_tower->t_last = NULL;
			}

			else {
				//Relie la tour suivante à la tour précédente de la tour que l'on veut supprmer 
				current->t_next->t_prev = current->t_prev;
				//Relie la tour précédente à la tour suivante de la tour que l'on veut supprmer 
				current->t_prev->t_next = current->t_next;

			}
			//supprime la tour
			free(current);
			list_tower->length--;

		}
		else {
			fprintf(stderr, "Tower doesn't exist");
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr, "Tower list doesn't exist");
		exit(EXIT_FAILURE);
	}
	return list_tower; 
}

void destroy_tower(List_Tower* list_tower) {
	//Si la liste n'est pas vide
	if (list_tower->length != 0) {
		free(list_tower);
	}
}


Tower* tower_on_select(Tower* t, List_Tower* l_tower, float x, float y){
	Tower* tu = l_tower->t_first;
	while(tu != NULL){
		if(square_intersect_circle(t->x, x, t->y, y, l_tower->length, 0)){
		    return tu;
		}
		tu = tu->t_next;
	}
    return 0;
}

int tower_on_construct(Map* map, int x, int y) {
	if(map->img->pixelData[(y*(map->img->width)+x)*3] == map->construct.r){
		if(map->img->pixelData[(y*(map->img->width)+x)*3+1] == map->construct.g){
			if(map->img->pixelData[(y*(map->img->width)+x)*3+2] == map->construct.b){
				return 1;
			}
		}
		else {
			fprintf(stderr, "zone non constructible\n");
			return 0;
		}
	}
	else{
		fprintf(stderr, "zone non constructible\n");
		return 0;
	}
	return 1;
}
#include <stdlib.h>
#include <stdio.h>
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

Tower* create_tower(Tower* t, TowerType type, float x, float y, int rate, int power, int range, int cost, Node* head){
	t->type = type; //type
	t->x = x; //coordonnee x
	t->y = y; //coordonnee y
	t->rate = rate; //La vitesse de tir
	t->power = power; //puissance de l'attaque
	t->range = range; //portee
	t->cost = cost; //prix
	t->node_prev = head; //Pointeur vers le premier noeud
	t->node_next = head->next; //Pointeur vers le second noeud
	t->node_next = NULL; 
	return t;
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


void destroy_tower(List_Tower* list_tower) {
	//Si la liste n'est pas vide
	if (list_tower->length != 0) {
		free(list_tower);
	}
}


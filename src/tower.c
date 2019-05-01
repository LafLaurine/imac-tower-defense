#include <stdlib.h>
#include <stdio.h>
#include "../include/tower.h"
#include "../include/geometry.h"


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

int tour_on_construct(List_Tower* list_tower, List_Node *list_node, Point2D pt1, Point2D pt2) {

	if(list_tower != NULL && list_node != NULL) {

		int i = 0;
		int quad = 0;
		Point2D point;

		for(i = 0; i < 4; i++) {

			//Vérifie avec les quatres points du quad
			switch(i) {
				case 0 : 
					point.x = pt1.x; 
					point.y = pt1.y;
					break;
				case 1 : 
					point.x = pt1.x; 
					point.y = pt2.y;
					break;
				case 2 :
					point.x = pt2.x; 
					point.y = pt2.y;
					break;
				case 3 :
					point.x = pt2.x; 
					point.y = pt1.y;
					break;
			}

			Node* tmp = list_node->head;

			while(tmp != NULL){

				if(point.x == tmp->x && point.y == tmp->y)
					quad++;

				tmp = tmp->next;
			}

		}

		//Si les 4 extremité sont dans la zone constructible
		if(quad < 4)
			return 0;
		//la tour est bien dasn zone constructible

	}
	else {
		fprintf(stderr, "Tower not on constructible material\n");
		return 0;
	}

	return 1;

}



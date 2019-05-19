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

Tower* create_tower(TowerType type, float x, float y, Node* head, List_Tower* l_tower){
	Tower* t = (Tower*)malloc(sizeof(Tower));
		
	if(t != NULL) {
		t->type = type; //type
		t->x = x; //coordonnee x
		t->y = y; //coordonnee y
		t->node_prev = head; //Pointeur vers le premier noeud
		t->node_next = head->next; //Pointeur vers le second noeud
		t->node_next = NULL; 
		t->t_next = NULL;

		if(type == LASER) {
			t->rate = 10; //La vitesse de tir
			t->power = 15; //puissance de l'attaque
			t->range = 5; //portee
			t->cost = 10; //prix
		}
		else if(type == ROCKET) {
			t->rate = 15;
			t->power = 10;
			t->range = 5;
			t->cost = 10;
		}
		else if(type == YELLOW) {
			t->rate = 20;
			t->power = 15;
			t->range = 5;
			t->cost = 10;
		}
		else if(type == BLUE) {
			t->rate = 50;
			t->power = 15;
			t->range = 5;
			t->cost = 100;
		}
		add_tower_list(t, l_tower);
		printf("%s\n", "New tower");
		return t;
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

int tower_on_tower(List_Tower* list_tower, float x, float y) {
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;

		while(t != NULL) {
			if(is_intersect(x, y, t->x, t->y, 34) == 1){
        		return 0;
			}
			t = t->t_next;
    	}
		return 1;
	}
	else {
		fprintf(stderr, "Tower not on constructible material\n");
		return 0;
	}
}

int is_intersect(float x1, float y1, float x2, float y2, float radius){
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < radius*radius*4;
}
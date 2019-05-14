#include <stdlib.h>
#include <stdio.h>
#include "../include/installation.h"

List_Installation* new_installation_list() {
	List_Installation *list_installation = malloc(sizeof(List_Installation));
	if (list_installation != NULL) {
		list_installation->length = 0;
		list_installation->t_first = NULL;
		list_installation->t_last = NULL;
	}
	else {
		printf("%s\n", "Not enough memory");
		return NULL;
	}
	return list_installation;
}

Installation* create_installation(Installation* t, InstallationType type, float x, float y, List_Tower list_tower){
	t->type = type; //type
	t->x = x; //coordonnee x
	t->y = y; //coordonnee y
	switch(type){
		case RADAR :
			break;
		case USINE : 
			break;
		case STOCK : 
			break;
		default : 
			printf("NOT WORKING");
			exit(EXIT_FAILURE);
			break;
	}
	return t;
}

void add_installation_list(Installation* t, List_Installation* list_installation){
	if (list_installation != NULL) {
		if (list_installation->t_last == NULL) {
				// Pointe la tête de la liste sur le nouveau monstre
				list_installation->t_first = t; 
				t->t_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				t->t_prev = list_installation->t_last; 
				list_installation->t_last->t_next = t;  
			}
			
			// Pointe la fin de la liste sur le nouveau monstre
			list_installation->t_last = t; 

			// On augmente de 1 la taille de la liste
			list_installation->length++; 
		}
	else {
		printf("%s\n", "Fail to add to list installation");
	}
}


void destroy_installation(List_Installation* list_installation) {
	//Si la liste n'est pas vide
	if (list_installation->length != 0) {
		free(list_installation);
	}
}


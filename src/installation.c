#include <stdlib.h>
#include <stdio.h>
#include "../include/installation.h"

List_Installation* new_installation_list() {
	List_Installation *list_installation = malloc(sizeof(List_Installation));
	if (list_installation != NULL) {
		list_installation->length = 0;
		list_installation->i_first = NULL;
		list_installation->i_last = NULL;
	}
	else {
		printf("%s\n", "Not enough memory");
		return NULL;
	}
	return list_installation;
}

Installation* create_installation(InstallationType type, float x, float y, List_Installation* list_inst){
	Installation* i = (Installation*)malloc(sizeof(Installation));

	if(i != NULL){
		i->type = type; //type
		i->x = x; //coordonnee x
		i->y = y; //coordonnee y
		i->i_next = NULL;

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

		add_installation_list(i, list_inst);
		printf("%s\n", "New installation");

	} else {
		printf("%s\n", "Not enough memory for installation");
		exit(EXIT_FAILURE);
	}

	return i;
}

void add_installation_list(Installation* i, List_Installation* list_installation){
	if (list_installation != NULL) {
		if (list_installation->i_last == NULL) {
				// Pointe la tête de la liste sur le nouveau monstre
				list_installation->i_first = i; 
				i->i_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				i->i_prev = list_installation->i_last; 
				list_installation->i_last->i_next = i;  
			}
			
			// Pointe la fin de la liste sur le nouveau monstre
			list_installation->i_last = i; 

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
	// FONCTION POUR ENLEVER POUVOIR AUX TOURS
}

int installation_on_construct(Map* map, int x, int y) {
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
	
}
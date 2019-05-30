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
			i->cost = 20;
				break;
			case USINE : 
			i->cost = 30;
				break;
			case STOCK : 
			i->cost = 50;
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

Installation* click_installation(List_Installation* l_install, float x, float y) {
	
	//Vérifie que la liste de tours existe
	if(l_install != NULL) {

		//Tour temporaire pour parcourir la liste de tour
		Installation* i_tmp = l_install->i_first;
		
		while(i_tmp != NULL) {

			//Si on a cliqué sur une tour
			if(x <= (i_tmp->x + 20) && x >= (i_tmp->x - 20) && y <= (i_tmp->y + 20) && y >= (i_tmp->y - 20)) {
				return i_tmp;	
			}

			i_tmp = i_tmp->i_next;

		}
	}
	else {
		fprintf(stderr, "Erreur :wrong liste installation\n");
		return NULL;
	}

	return NULL;

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

Installation* installation_on_select(Installation* i, List_Installation* l_inst, float x, float y){
	while(i != NULL){
		if(square_intersect_square(i->x, x, i->y, y, l_inst->length, 0)){
		    return i;
		}
		i = l_inst->i_first->i_next;
	}
    return 0;
}

//delete installation from list and return list of installation
List_Installation* delete_install_from_position(List_Installation* l_inst, Installation* current) {
	if (l_inst != NULL) {
		if(current != NULL) {
			//Si c'est la dernièl'installation de la liste
			if (current->i_next == NULL) {
				
				//Pointe la fin de la liste sur l'installation précédente
				l_inst->i_last = current->i_prev;

				if(l_inst->i_last != NULL) {
					//Lien de la dernière installation vers l'installation suivante est NULL
					l_inst->i_last->i_next = NULL;
				}
				else
					l_inst->i_first = NULL;
					
			}
			//Si c'est la première de la liste
			else if (current->i_prev == NULL) {
				l_inst->i_first = current->i_next;

				if(l_inst->i_first != NULL) {
			 		l_inst->i_first->i_prev = NULL;
				}
				else
					l_inst->i_last = NULL;
			}
			else {
				//Relie l'installation suivante à l'installation précédente de l'installation que l'on veut supprmer 
				current->i_next->i_prev = current->i_prev;
				//Relie l'installation précédente à l'installation suivante de l'installation que l'on veut supprmer 
				current->i_prev->i_next = current->i_next;

			}
			//supprime l'installation
			free(current);
			l_inst->length--;

		}
		else {
			fprintf(stderr, "Installation doesn't exist");
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr, "Installation list doesn't exist");
		exit(EXIT_FAILURE);
	}
	return l_inst; 
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
	return 1;
}
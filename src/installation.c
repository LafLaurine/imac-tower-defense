#include "../include/installation.h"

List_Installation* new_installation_list() {
	List_Installation *l_inst = malloc(sizeof(List_Installation));
	if (l_inst != NULL) {
		l_inst->length = 0;
		l_inst->i_first = NULL;
		l_inst->i_last = NULL;
	} else {
		printf("Not enough memory\n");
		exit(EXIT_FAILURE);
	}
	return l_inst;
}

Installation* create_installation(InstallationType type, float x, float y, List_Installation* l_inst, int money){
	Installation* i = (Installation*)malloc(sizeof(Installation));
	
	if(i != NULL){
		i->type = type; //type
		i->x = x; //coordonnee x
		i->y = y; //coordonnee y
		i->i_next = NULL;

		switch(type){
			case RADAR :
				i->cost = 150;
			break;
			case USINE : 
				i->cost = 150;
			break;
			case STOCK : 
				i->cost = 150;
			break;
			default : 
				exit(EXIT_FAILURE);
			break;
		}

		// Check if enough money to buy installation
		if(money >= i->cost) {
			add_installation_list(i, l_inst);
			printf("New installation\n");
			return i;
		} else {
			printf("Not enough money to buy an installation");
			return NULL;
		}

	} else {
		printf("Not enough memory for installation\n");
		exit(EXIT_FAILURE);
	}
}

Installation* click_installation(List_Installation* l_inst, float x, float y) {
	// Check if list installation exists
	if(l_inst != NULL) {

		// Temp installation to browse list
		Installation* i_tmp = l_inst->i_first;
		
		while(i_tmp != NULL) {
			// If click was on installation
			if(x <= (i_tmp->x + 20) && x >= (i_tmp->x - 20) && y <= (i_tmp->y + 20) && y >= (i_tmp->y - 20)) {
				return i_tmp;	
			}
			i_tmp = i_tmp->i_next;
		}
		
	} else {
		printf("Erreur :wrong liste installation\n");
		exit(EXIT_FAILURE);
	}
	return NULL;
}

void add_installation_list(Installation* i, List_Installation* l_inst){
	if (l_inst != NULL) {
		if (l_inst->i_last == NULL) {
				// List head on new installation
				l_inst->i_first = i; 
				i->i_prev = NULL;
			}
			// If elements are already into list
			else {
				i->i_prev = l_inst->i_last; 
				l_inst->i_last->i_next = i;  
			}
			
		// List last on new installation
		l_inst->i_last = i; 
		// List length +1
		l_inst->length++; 
	} else {
		printf("Fail to add to list installation\n");
	}
}

void delete_install_from_position(List_Installation* l_inst, Installation* current) {
	if (l_inst != NULL) {
		if(current != NULL) {
			// If last installation of list
			if (current->i_next == NULL) {
				
				// End of list on previous installation
				l_inst->i_last = current->i_prev;

				if(l_inst->i_last != NULL) {
					// Last installation next is NULL
					l_inst->i_last->i_next = NULL;
				}
				else
					l_inst->i_first = NULL;	
			}
			// If first of list
			else if (current->i_prev == NULL) {
				l_inst->i_first = current->i_next;

				if(l_inst->i_first != NULL) {
			 		l_inst->i_first->i_prev = NULL;
				}
				else
					l_inst->i_last = NULL;

			} else {
				// Link next installation to previous installation (soon deleted)
				current->i_next->i_prev = current->i_prev;
				// Link previous installation to next installation (soon deleted)
				current->i_prev->i_next = current->i_next;
			}

			// Delete installation
			free(current);
			l_inst->length--;

		} else {
			printf("Installation doesn't exist\n");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("Installation list doesn't exist\n");
		exit(EXIT_FAILURE);
	}
}

void destroy_installation(List_Installation* l_inst) {
	// If list not empty
	if (l_inst->length != 0) {
		free(l_inst);
	}
}

int installation_on_construct(Map* map, int x, int y) {
	// Check pixel if (x,y) pixel color corresponds to construct color
	if(map->img->pixelData[(y*(map->img->width)+x)*3] == map->construct.r){
		if(map->img->pixelData[(y*(map->img->width)+x)*3+1] == map->construct.g){
			if(map->img->pixelData[(y*(map->img->width)+x)*3+2] == map->construct.b){
				return 1;
			}
		} else {
			printf("Non buildable area\n");
			return 0;
		}
	} else {
		printf("Non buildable area\n");
		return 0;
	}
	return 1;
}

List_Installation* remove_installation(List_Installation* current_i, Installation* current) {
	// Check if list allocated
	if (current_i != NULL) {
		if(current != NULL) {
			// List head on next node
			current_i->i_first = current->i_next;
			free(current);
			current_i->length--;

		} else
			printf("Inexistant installation\n");
	} else 
		printf("Couldn't find list\n");

	// Return new list
	return current_i; 
}

void free_all_inst(List_Installation* l_inst) {
	// If list not empty
	if (l_inst->length != 0) {
		//	While list not NULL
		Installation* temp = l_inst->i_last;
		while(temp != NULL) {
			if(temp->i_prev != NULL){
				l_inst = remove_installation(l_inst, temp->i_next);
				temp = temp->i_prev;
			} else {
				l_inst = remove_installation(l_inst, temp);
				temp = NULL;
			}
		}
	}
	free(l_inst);
}
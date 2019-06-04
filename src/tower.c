#include "../include/tower.h"

List_Tower* new_tower_list() {
	List_Tower *l_tower = malloc(sizeof(List_Tower));
	if (l_tower != NULL) {
		l_tower->length = 0;
		l_tower->t_first = NULL;
		l_tower->t_last = NULL;
	}
	else {
		printf("Not enough memory\n");
		exit(EXIT_FAILURE);
	}
	return l_tower;
}

Tower* create_tower(TowerType type, float x, float y, List_Tower* l_tower, int money){
	Tower* t = malloc(sizeof(Tower)); 
	
	if(t != NULL) {
		t->type = type; // Type
		t->x = x; // x Position
		t->y = y; // y Position
		t->t_next = NULL; // Next tower
		t->t_prev = NULL; // Previous tower

		if(type == LASER) {
			t->rate = 10; // Shooting rate
			t->power = 5; // Shooting power
			t->range = 50; // Shooting range
			t->cost = 10; // Tower cost
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
		printf("New tower\n");
		
		// Check if enough money to buy tower
		if(money >= t->cost) {
			return t;
		} else {
			printf("Not enough money to buy tower");
			return NULL;
		}

	} else {
		printf("Not enough memory for tower\n");
		exit(EXIT_FAILURE);
	}
}

void add_tower_list(Tower* t, List_Tower* l_tower){
	if (l_tower != NULL) {
		if (l_tower->t_last == NULL) {
				// List head on new tower
				l_tower->t_first = t; 
				t->t_prev = NULL;
			}
			// If elements are already into list
			else {
				t->t_prev = l_tower->t_last; 
				l_tower->t_last->t_next = t;  
			}
			
			// List last on new tower
			l_tower->t_last = t; 
			// List length +1
			l_tower->length++; 

		} else {
			printf("Fail to add to list tower\n");
	}
}


Tower* click_tower(List_Tower* l_tower, float x, float y) {
	// Check if list tower exists
	if(l_tower != NULL) {

		// Temp tower to browse list
		Tower* p_tmp = l_tower->t_last;
		
		while(p_tmp != NULL) {
			/// If click was on tower
			if(x <= (p_tmp->x + 50) && x >= (p_tmp->x - 50) && y <= (p_tmp->y + 50) && y >= (p_tmp->y - 50)) {
				return p_tmp;	
			}
			p_tmp = p_tmp->t_prev;
		}

	} else {
		printf("Erreur :wrong liste tour\n");
		return NULL;
	}
	return NULL;
}

void delete_from_position(List_Tower* l_tower, Tower* current) {
	if (l_tower != NULL) {
		if(current != NULL) {
			// If last installation of list
			if (current->t_next == NULL) {
				
				// End of list on previous installation
				l_tower->t_last = current->t_prev;

				if(l_tower->t_last != NULL) {
					// Last installation next is NULL
					l_tower->t_last->t_next = NULL;
				}
				else
					l_tower->t_first = NULL;
			}

			// If first of list
			else if (current->t_prev == NULL) {
				l_tower->t_first = current->t_next;

				if(l_tower->t_first != NULL) {
			 		l_tower->t_first->t_prev = NULL;
				}
				else
					l_tower->t_last = NULL;

			} else {
				// Link next tower to previous tower (soon deleted) 
				current->t_next->t_prev = current->t_prev;
				// Link previous tower to next tower (soon deleted)
				current->t_prev->t_next = current->t_next;
			}

			// Delete tower
			free(current);
			l_tower->length--;

		} else {
			printf("Tower doesn't exist\n");
			exit(EXIT_FAILURE);
		}
	} else {
		printf("Tower list doesn't exist\n");
		exit(EXIT_FAILURE);
	}
}

void destroy_tower(List_Tower* l_tower) {
	// Check if list not empty
	if (l_tower->length != 0) {
		free(l_tower);
	}
}

int tower_on_construct(Map* map, int x, int y) {
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
	} else{
		printf("Non buildable area\n");
		return 0;
	}
	return 1;
}
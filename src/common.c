#include "../include/common.h"

int is_intersect(float x1, float y1, float x2, float y2, float r1, float r2){
	// Pythagore theorem
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < (r1+r2)*(r1+r2);
}

void vBitmapOutput(int x, int y, char *string, void *font) {
	int len,i; // string length

	glRasterPos2f(x,y); // First character position
	len = (int) strlen(string); // Calculate length string
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font,string[i]); // Display each string character
	}
	// to first character position
	glRasterPos2f(0, 0);
}

Tower* constructTowerSelected(List_Tower* l_tower, int x, int y) {
	// Check all towers of list tower
	if(l_tower != NULL) {
		Tower* currTower = l_tower->t_last;

		while(currTower != NULL) {
			// Hover tower ?
			if(x >= ((*currTower).x - 50) && x <= ((*currTower).x + 50) && y >= ((*currTower).y - 50) && y <= ((*currTower).y + 50)) {
				return currTower;
			} else {
				currTower = currTower->t_prev;
			}
		}
	}
	return NULL;
}

Installation* select_installation_construted(List_Installation* l_inst, int x, int y) {
	// Check all installation of list installation
	if(l_inst != NULL) {
		Installation* current = l_inst->i_last;
		while(current != NULL) {
			// Hover installation ?
			if(x >= ((*current).x - 50) && x <= ((*current).x + 50) && y >= ((*current).y - 50) && y <= ((*current).y + 50)) {
				return current;
			} else {
				current = current->i_prev;
			}
		}
	}
	return NULL;
}

int tower_on_building(List_Tower* list_tower, float x, float y, List_Installation* list_inst) {
	// Check all towers of list tower
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;

		while(t != NULL) {
			if(is_intersect(x, y, t->x, t->y, TOWERRAY, TOWERRAY) == 1){
        		return 0;
			}
			t = t->t_next;
    	}
		// Check all installation of list installation
		if(list_inst != NULL) {
			Installation* i = list_inst->i_first;

			while(i != NULL) {
				if(is_intersect(x, y, i->x, i->y, TOWERRAY, TOWERRAY) == 1){
					return 0;
				}
				i = i->i_next;
			}
		}

		return 1;
	}
	else {
		fprintf(stderr, "Tower not on constructible material\n");
		return 0;
	}
}

int inst_on_building(List_Installation* list_inst, float x, float y, List_Tower* list_tower) {
	// Check all installations of list installation
	if(list_inst != NULL) {
		Installation* i = list_inst->i_first;
		
		while(i != NULL) {
			if(is_intersect(x, y, i->x, i->y, TOWERRAY, INSTALLRAY) == 1){
        		return 0;
			}
			i = i->i_next;
    	}

		if(list_tower != NULL) {
			Tower* t = list_tower->t_first;

			while(t != NULL) {
				if(is_intersect(x, y, t->x, t->y, TOWERRAY, INSTALLRAY) == 1){
					return 0;
				}
				t = t->t_next;
			}
		}
		return 1;
	}
	else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

int check_around_tower(Tower* t, List_Installation* list_inst){
	// Check all installations of list installation
	if(list_inst != NULL) {
		Installation* i = list_inst->i_first;
		
		while(i != NULL) {
			if(is_intersect(t->x, t->y, i->x, i->y, TOWERRAY+t->range, TOWERRAY) == 1){
				update_tower(t, i->type);
			}
			i = i->i_next;
    	}
		return 0;
	}
	else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

int click_delete_tower(List_Tower* l_tower, Tower* current, Game* game) {
	// Check all towers of list tower
	if(l_tower != NULL) {
		if(current != NULL) {
			player_money_up_update(game,current->cost);
			delete_from_position(l_tower, current);
		}
	} else {
		fprintf(stderr, "Erreur current tower\n");
		return 0;
	}
	return 1;
}

int click_installation_delete(List_Installation* l_inst, Installation* current, Game* game, List_Tower* l_tower) {
	// Check all installations of list tower
	if(l_inst != NULL) {
		if(current != NULL) {
			player_money_up_update(game,current->cost);
			delete_around_inst(current, l_tower);
			delete_install_from_position(l_inst, current);	
		}
	} else {
		fprintf(stderr, "Erreur current installation\n");
		return 0;
	}
	return 1;
}

int check_around_inst(Installation* i, List_Tower* list_tower){
	// Check all towers of list tower
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;
		while(t != NULL) {
			if(is_intersect(i->x, i->y, t->x, t->y, 30+t->range, 30)){
				update_tower(t, i->type);
			}
			t = t->t_next;
    	}
		return 0;
	} else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

void update_tower(Tower* t, InstallationType type_inst){
	// Update according to type
	if(type_inst == 0){
		t->range += (t->range)*0.25;
	} else if(type_inst == 1) {
		t->power += (t->power)*0.25;
	} else {
		t->rate += (t->rate)*0.25;		
	}
}


int delete_around_inst(Installation* i, List_Tower* list_tower){
	// Check all towers of list tower
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;
		
		while(t != NULL) {
			if(is_intersect(t->x, t->y, i->x, i->y, TOWERRAY+t->range, INSTALLRAY)){
				downgrade_tower(t, i->type);
			}
			t = t->t_next;
    	}
		return 0;
	} else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

void downgrade_tower(Tower* t, InstallationType type_inst){
	// Downgrade according to type
	if(type_inst == 0){
		t->range -= (t->range)*0.25;
	} else if(type_inst == 1) {
		t->power -= (t->power)*0.25;
	} else {
		t->rate -= (t->rate)*0.25;		
	}
}

// MONSTER AND TOWERS
Monster_Type monster_on_tower(List_Monster* list_monster, List_Tower* list_tower) {
	// Check all towers of list tower
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;
		int compteurTour = 0;
		int compteurMonstre = 0;
		Monster_Type monsterKilled = -1;

		while(t != NULL){
			Mix_Music *musique; // Pointer type Mix_Music
									Mix_AllocateChannels(16);


			if(list_monster != NULL) {
				Monster* m = list_monster->m_first;

				while(m != NULL) {
					if(shot_monster(m,t)){
						
						// Display shots
						glBegin(GL_LINES);
							glColor3ub(255,0,0);
							glVertex2f(t->x, t->y);
							glVertex2f(m->x, m->y);
						glEnd();

						//Display music
						musique = Mix_LoadMUS("./son/pew.wav"); // Load music
						Mix_PlayMusic(musique, 1); // Play music

						if(m->pv <= 0){ // Monster has 0pv
							monsterKilled = kill_monster(list_monster, m);
							musique = Mix_LoadMUS("./son/dead_monster.mp3"); // Load music
							Mix_PlayMusic(musique, 1); // Play music
						}
					}
					m = m->m_next;
					compteurMonstre++;
				}
			}
			compteurTour++;
			t = t->t_next;	
		}
		return monsterKilled;
	}
	else {
		fprintf(stderr, "No monsters here\n");
		return -1;
	}
}

int shot_monster(Monster* m, Tower* t) {
	// If monster intersects with tower : shot
	if(is_intersect(t->x, t->y, m->x, m->y, TOWERRAY+t->range, MONSTERRAY)) {
		m->pv = m->pv - t->power;
		return 1;
	}
	return 0;
}

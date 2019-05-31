#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/display.h"

int display_map(GLuint* texture) {

	if(texture != NULL) {
		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture

		glBindTexture(GL_TEXTURE_2D, *texture);

			glBegin(GL_QUADS);
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(600, 600);

			glTexCoord2f(1, 0);
			glVertex2f(600, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 600);

			glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		fprintf(stderr, "Erreur la texture de la map n'existe pas\n");
		return 0;
	}

	return 1;

}

//perimetre action sous forme de cdisque
void draw_perim(float rayon) {
	
	int i, j = 100;
	float angle, x1, y1;
	
	glBegin(GL_TRIANGLE_FAN);

	glVertex2f(0, 0);

	for(i = 0; i <= j; i++) {
		angle = (2*3.14*i)/j;
		x1 = rayon*(cos(angle));
		y1 = rayon*(sin(angle));
		glVertex2f(x1,y1);
	}

	glEnd();

}

int display_path(Map* map) {

	if(map != NULL) {

		Node* tmp = map->list_node->head;

		while(tmp->next != NULL) {
		
			//node
			glBegin(GL_LINES);
				glColor3ub(0,0,0);
				glVertex2d(tmp->x, tmp->y);
				glVertex2d(tmp->next->x, tmp->next->y);
			glEnd();

			glPushMatrix();
				glColor3ub((map->node).r,(map->node).g,(map->node).b);
				glTranslatef(tmp->x,tmp->y, 0.0);
				draw_perim(2);
			glPopMatrix();
			//path
			glColor3ub(255,255,255);

			tmp = tmp->next;					

		}
	}
	else {
		fprintf(stderr, "Map doesn't exist\n");
		return 0;
	}

	return 1;
}

int display_full(GLuint* texture) {
	if(texture != NULL) {
		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(1000,600);
			glTexCoord2f(1, 0);
			glVertex2f(1000, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 600);
			glEnd();
		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);		
	}
	else {
		fprintf(stderr, "Couldn't find texture\n");
		return 0;
	}

	return 1;
}

//display money
int display_money(GLuint* texture) {

	if(texture != NULL) {

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(30, 13);
			glTexCoord2f(1, 0);
			glVertex2f(30, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 13);
			glEnd();
		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		
	}
	else {
		fprintf(stderr, "Couldn't find money\n");
		return 0;
	}

	return 1;
}

//display cross
int display_cross(GLuint* texture) {

	if(texture != NULL) {

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *texture);
			glBegin(GL_QUADS);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(20, 20);
			glTexCoord2f(1, 0);
			glVertex2f(20, 0);
			glTexCoord2f(0, 0);
			glVertex2f(0, 0);
			glTexCoord2f(0, 1);
			glVertex2f(0, 20);
			glEnd();
		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		
	}
	else {
		fprintf(stderr, "Couldn't find cross\n");
		return 0;
	}

	return 1;

}

//display right column
void display_right_column() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3ub(255,255,255);
	glBegin(GL_QUADS);
		//Cordonnée du quadrilatère 
		glVertex2f(400, 600);
		glVertex2f(400, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 600);
	glEnd();
}


// MONSTER

int display_monster(Monster* m, SDL_Surface* img, GLuint texture) {
	if(m->node_next != NULL) {
		if(m->move == m->speed) {
			// Déplacement horizontal du monstre
			if(m->node_next->y == m->y) {
				// Vers la droite
				if(m->node_next->x > m->x) {
					m->x += 1;
				}
				// Vers la gauche
				else {
					m->x -= 1;
				}   
			}
			// Déplacement vertical du monstre
			else {
				// Vers le bas
				if(m->node_next->y > m->y) {
					m->y += 1;
				}
				// Vers le haut
				else {
					m->y -= 1;
				}
			}

			if(m->x == m->node_next->x && m->y == m->node_next->y) {
				m->node_next = m->node_next->next;
			}

			m->move = 0;
		}
		else {
			m->move += 1;
		}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBegin(GL_QUADS);
			glColor3ub(255, 255, 255); // couleur neutre
			glTexCoord2d(0, 1); glVertex2d(m->x + img->w * 0.5, m->y + img->h * 0.5);
			glTexCoord2d(0, 0); glVertex2d(m->x + img->w * 0.5, m->y - img->h * 0.5);
			glTexCoord2d(1, 0); glVertex2d(m->x - img->w * 0.5, m->y - img->h * 0.5);
			glTexCoord2d(1, 1); glVertex2d(m->x - img->w * 0.5, m->y + img->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		// Jauge de vie
		glBegin(GL_QUADS);
		glColor3ub(255, 0, 0);
		glVertex2d(m->x, m->y + 30);
		glVertex2d(m->x, m->y + 40);
		if(m->pv_max > 0 && m->pv_max < 1) {
			glVertex2d(m->x + 1, m->y + 30);
			glVertex2d(m->x + 1, m->y + 40);
		}
		else {
			glVertex2d(m->x + m->pv_max / 2, m->y + 30);
			glVertex2d(m->x + m->pv_max / 2, m->y + 40);
		}	
		glEnd();

		

		return 1;
	}
	return 0;
}

int display_wave(List_Monster *l_monster) {
	SDL_Surface* bactery = IMG_Load("./images/bactery.png");
	if(bactery == NULL) {
		fprintf(stderr, "impossible de charger l'image bactery.png \n");
		exit(1);
	}
	SDL_Surface* virus = IMG_Load("./images/virus.png");
	if(virus == NULL) {
		fprintf(stderr, "impossible de charger l'image virus.png \n");
		exit(1);
	}
	GLuint texture_bactery;
	load_sprite("./images/bactery.png",&texture_bactery);
	GLuint texture_virus;
	load_sprite("./images/virus.png",&texture_virus);

	/*Monster* m;
	int success = 1;
	for(int i = 0; i < wave.nb_lists; i++) {
		m = wave.lists[i]->m_first;
		while(m != NULL) {
			if(m->type == BACTERY) {
				if(display_monster(m, bactery, texture_bactery) == 0) {
					success = 0;
				}
			}
			else {
				if(display_monster(m, virus, texture_virus) == 0) {
					success = 0;
				}
			}
			m = m->m_next;
		}
	}*/

	Monster* m;
	int success = 1;
	m = l_monster->m_first;

		while(m != NULL) {
			if(m->type == BACTERY) {
				if(display_monster(m, bactery, texture_bactery) == 0) {
					success = 0;
				}
			}
			else {
				if(display_monster(m, virus, texture_bactery) == 0) {
					success = 0;
				}
			}
			m = m->m_next;
		}

	SDL_FreeSurface(bactery);
	SDL_FreeSurface(virus);

	return success;
}


// TOWERS

int display_tower(Tower* t, SDL_Surface* tourImg, GLuint *tourTexture) {
	if(t != NULL) {

		display_range_tower(t);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, *tourTexture);

		glBegin(GL_QUADS);
			glColor3ub(255, 255, 255); // couleur neutre
			glTexCoord2d(0, 1); glVertex2d(t->x + tourImg->w * 0.5, t->y + tourImg->h * 0.5);
			glTexCoord2d(0, 0); glVertex2d(t->x + tourImg->w * 0.5, t->y - tourImg->h * 0.5);
			glTexCoord2d(1, 0); glVertex2d(t->x - tourImg->w * 0.5, t->y - tourImg->h * 0.5);
			glTexCoord2d(1, 1); glVertex2d(t->x - tourImg->w * 0.5, t->y + tourImg->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		return 1;
	}
	return 0;
}

int display_list_tower(List_Tower* list_tower) {
	int success = 1;
	
	if(list_tower->t_first == NULL){
		return success;
	} else {
		SDL_Surface* rocket = IMG_Load("./images/towers/rocket.png");

		if(rocket == NULL) {
			fprintf(stderr, "impossible de charger l'image rocket.png \n");
			exit(1);
		}
		
		SDL_Surface* laser = IMG_Load("./images/towers/laser.png");
		if(laser == NULL) {
			fprintf(stderr, "impossible de charger l'image laser.png \n");
			exit(1);
		}
		GLuint texture_rocket;
		load_sprite("./images/towers/tower_3.png",&texture_rocket);
		GLuint texture_laser;
		load_sprite("./images/towers/laser.png",&texture_laser);

		Tower* t;
		t = list_tower->t_first;

		while(t != NULL) {
			if(t->type == ROCKET) {
				if(display_tower(t, rocket, &texture_rocket) == 0) {
					success = 0;
				}
			}
			else if(t->type == LASER) {
				if(display_tower(t, laser, &texture_laser) == 0) {
					success = 0;
				}
			} else {
				printf("NO");
			}
			t = t->t_next;
		}

		SDL_FreeSurface(rocket);
		SDL_FreeSurface(laser);

		return success;
	}
}

int display_range_tower(Tower* t) {
	if(t != NULL) {
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0,0.0,0.0,0.5);
			glTranslatef(t->x,t->y, 0.0);
			glScalef(t->range+64,t->range+64,0);
			drawCircle(1, 50);
		glPopMatrix();

		return 1;
	}
	return 0;
}
// INSTALLATION

int display_installation(Installation* i, SDL_Surface* instImg, GLuint *instTexture) {
	if(i != NULL) {
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, *instTexture);

		glBegin(GL_QUADS);
			glColor3ub(255, 255, 255); // couleur neutre
			glTexCoord2d(0, 1); glVertex2d(i->x + instImg->w * 0.5, i->y + instImg->h * 0.5);
			glTexCoord2d(0, 0); glVertex2d(i->x + instImg->w * 0.5, i->y - instImg->h * 0.5);
			glTexCoord2d(1, 0); glVertex2d(i->x - instImg->w * 0.5, i->y - instImg->h * 0.5);
			glTexCoord2d(1, 1); glVertex2d(i->x - instImg->w * 0.5, i->y + instImg->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		return 1;
	}
	return 0;
}

int display_list_installation(List_Installation* list_inst) {
	int success = 1;
	
	if(list_inst->i_first == NULL){
		return success;
	} else {
		SDL_Surface* radar = IMG_Load("./images/installations/radar.png");

		if(radar == NULL) {
			fprintf(stderr, "impossible de charger l'image radar.png \n");
			exit(1);
		}
		
		SDL_Surface* usine = IMG_Load("./images/installations/usine.png");
		if(usine == NULL) {
			fprintf(stderr, "impossible de charger l'image usine.png \n");
			exit(1);
		}
		
		GLuint texture_radar;
		load_sprite("./images/installations/radar.png",&texture_radar);
		GLuint texture_usine;
		load_sprite("./images/installations/usine.png",&texture_usine);
		GLuint texture_stock;
		load_sprite("./images/installations/usine.png",&texture_stock);

		Installation* i;
		i = list_inst->i_first;

		while(i != NULL) {
			if(i->type == RADAR) {
				if(display_installation(i, radar, &texture_radar) == 0) {
					success = 0;
				}
			}
			else if(i->type == USINE) {
				if(display_installation(i, usine, &texture_usine) == 0) {
					success = 0;
				}
			}
			else if(i->type == STOCK) {
				if(display_installation(i, usine, &texture_stock) == 0) {
					success = 0;
				}
			}  
			else {
				printf("NO");
			}
			i = i->i_next;
		}

		SDL_FreeSurface(radar);
		SDL_FreeSurface(usine);

		return success;
	}
}

// CHECK IF DISPLAY IS POSSIBLE

int tower_on_building(List_Tower* list_tower, float x, float y, List_Installation* list_inst) {
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;

		while(t != NULL) {
			if(is_intersect(x, y, t->x, t->y, 34, 34) == 1){
        		return 0;
			}
			t = t->t_next;
    	}

		if(list_inst != NULL) {
			Installation* i = list_inst->i_first;

			while(i != NULL) {
				if(is_intersect(x, y, i->x, i->y, 34, 34) == 1){
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
	if(list_inst != NULL) {
		Installation* i = list_inst->i_first;
		
		while(i != NULL) {
			if(is_intersect(x, y, i->x, i->y, 34, 34) == 1){
        		return 0;
			}
			i = i->i_next;
    	}

		if(list_tower != NULL) {
			Tower* t = list_tower->t_first;

			while(t != NULL) {
				if(is_intersect(x, y, t->x, t->y, 34, 34) == 1){
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


// OTHER

void drawCircle (int fill, int nbSeg) {
    float teta = 0;
    glBegin(GL_POLYGON);
    if (fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    for (teta=0; teta<=2*PI; teta+=2*PI/nbSeg) {
        glVertex2f(0.5*cos(teta),0.5*sin(teta));
    }
    glEnd();       
}



int check_around_tower(Tower* t, List_Installation* list_inst){

	if(list_inst != NULL) {
		Installation* i = list_inst->i_first;
		
		while(i != NULL) {
			if(is_intersect(t->x, t->y, i->x, i->y, 34+t->range, 34) == 1){
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

int click_delete_tower(List_Tower* l_tower, Tower* current, Game* game, float x, float y) {
	if(l_tower != NULL) {
		if(current != NULL) {
			if(tower_on_select(current,l_tower,x,y)) {
				game->money += current->cost;
				l_tower = delete_from_position(l_tower, current);
				}
		}
		}
		else {
			fprintf(stderr, "Erreur la tour courante\n");
			return 0;
		}
	return 1;

}

int click_installation_delete(List_Installation* l_inst, Installation* current, Game* game, float x, float y) {
	if(l_inst != NULL) {
		if(current != NULL) {
			if(installation_on_select(current,l_inst,x,y)) {
				game->money += current->cost;
				l_inst = delete_install_from_position(l_inst, current);
			}
		}
		}
		else {
			fprintf(stderr, "Erreur installation courante\n");
			return 0;
		}
	return 1;

}

int check_around_inst(Installation* i, List_Tower* list_tower){

	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;
		
		while(t != NULL) {
			if(is_intersect(i->x, i->y, t->x, t->y, 34+t->range, 34)){
				update_tower(t, i->type);
			}
			t = t->t_next;
    	}
		return 0;
	}
	else {
		fprintf(stderr, "Installation not on constructible material\n");
		return 0;
	}
}

void update_tower(Tower* t, InstallationType type_inst){
	if(type_inst == 0){
		t->range += (t->range)*0.25;
	} else if(type_inst == 1) {
		t->power += (t->power)*0.25;
	} else {
		t->rate += (t->rate)*0.25;		
	}
}

// MONSTER AND TOWERS

int monster_on_tower(List_Monster* list_monster, List_Tower* list_tower) {
	if(list_tower != NULL) {
		Tower* t = list_tower->t_first;
		int compteurTour = 0;
		int compteurMonstre = 0;

		while(t != NULL){

			if(list_monster != NULL) {
				Monster* m = list_monster->m_first;

				while(m != NULL) {
					if(shot_monster(m,t)){
						if(m->pv <= 0){
							kill_monster(list_monster, m);
						}
					}
					m = m->m_next;
					compteurMonstre++;
				}
			}
			compteurTour++;
			t = t->t_next;
		}
		return 1;
	}
	else {
		fprintf(stderr, "No monsters here\n");
		return 0;
	}
}

int shot_monster(Monster* m, Tower* t) {
	if(is_intersect(t->x, t->y, m->x, m->y, 34+t->range, 34)) {
		m->pv = m->pv - t->power;
		printf("PV MONSTRE %d",m->pv);
		return 1;
	}
	return 0;
}
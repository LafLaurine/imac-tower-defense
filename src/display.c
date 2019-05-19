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
			glVertex2f(500, 300);

			glTexCoord2f(1, 0);
			glVertex2f(500, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 300);

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

int display_help(GLuint* texture) {

	if(texture != NULL) {

		//Active le texturage 2D
		glEnable(GL_TEXTURE_2D);
		//appel de la texture
		glBindTexture(GL_TEXTURE_2D, *texture);

			glBegin(GL_QUADS);
			//couleur neutre
			glColor3ub(255,255,255);
			//coordonée de la texture
			glTexCoord2f(1, 1);
			//Cordonnée du quadrilatère 
			glVertex2f(500, 300);

			glTexCoord2f(1, 0);
			glVertex2f(500, 0);

			glTexCoord2f(0, 0);
			glVertex2f(0, 0);

			glTexCoord2f(0, 1);
			glVertex2f(0, 300);

			glEnd();

		//Déblinder la texture
		glBindTexture(GL_TEXTURE_2D, 0);
		//Désactive le texturage 2D
		glDisable(GL_TEXTURE_2D);

		
	}
	else {
		fprintf(stderr, "Couldn't find help\n");
		return 0;
	}

	return 1;

}


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
		glTexCoord2d(0, 1); glVertex2d(m->x + img->w * 0.5, 300-m->y + img->h * 0.5);
		glTexCoord2d(0, 0); glVertex2d(m->x + img->w * 0.5, 300-m->y - img->h * 0.5);
		glTexCoord2d(1, 0); glVertex2d(m->x - img->w * 0.5, 300-m->y - img->h * 0.5);
		glTexCoord2d(1, 1); glVertex2d(m->x - img->w * 0.5, 300-m->y + img->h * 0.5);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		return 1;
	}
	return 0;
}

int display_wave(Wave wave) {
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

	Monster* m;
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
	}

	SDL_FreeSurface(bactery);
	SDL_FreeSurface(virus);

	return success;
}

/*
TowerType choose_tower_type(int x, int y) {
	// Si "ROCKET"
	if(x >= ? && x <= ? && y >= ? && y <= ?) {
		printf("ROCKET !\n");
		type = ROCKET;
	}
	// Si "MITRAILLETTE"
	if(x >= ? && x <= ? && y >= ? && y <= ?) {
		type = MITRAILLETTE;
	}
	// Si "LASER"
	if(x >= ? && x <= ? && y >= ? && y <= ?) {
		type = LASER;
	}
	// Si "HYBRIDE"
	if(x >= ? && x <= ? && y >= ? && y <= ?) {
		type = HYBRIDE;
	}

	return type;
}*/

/*

void display_tower(Tower* current, SDL_Surface* tourImg, GLuint *tourTexture) {
	while(current != NULL) {
		// Chargement de l'image de la tour en fonction de son type
		if(current->type == ROCKET) {
			tourImg = IMG_Load("");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image \n");
		        exit(1);
		    }
		    tourTexture = load_sprite("images/towers/rocket.png");
		}
		else if(current->type == LASER) {
			tourImg = IMG_Load("");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image\n");
		        exit(1);
		    }
		    tourTexture = load_sprite("");		
		}
		else if(current->type == YELLOW) {
			tourImg = IMG_Load("");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image\n");
		        exit(1);
		    }
		    tourTexture = load_sprite("");
		}
		else if(current->type == BLUE) {
			tourImg = IMG_Load("");
		    if(tourImg == NULL) {
		        fprintf(stderr, "impossible de charger l'image\n");
		        exit(1);
		    }
		    tourTexture = load_sprite("");
		}
		
		// Affichage de la texture sur la carte
		glEnable(GL_TEXTURE_2D);
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glBindTexture(GL_TEXTURE_2D, tourTexture);
	    
		glBegin(GL_QUADS);
			glColor4ub(255, 255, 255, 255); // Opacité 100%
			glTexCoord2d(0, 0); glVertex2f(current->x - tourImg->w * 0.5, current->y + tourImg->h * 0.5);
			glTexCoord2d(0, 1); glVertex2f(current->x - tourImg->w * 0.5, current->y - tourImg->h * 0.5);
			glTexCoord2d(1, 1); glVertex2f(current->x + tourImg->w * 0.5, current->y - tourImg->h * 0.5);
			glTexCoord2d(1, 0); glVertex2f(current->x + tourImg->w * 0.5, current->y + tourImg->h * 0.5);
		glEnd();
	    
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_BLEND);
	    glDisable(GL_TEXTURE_2D);

	    current = current->t_next;
    }

    glDeleteTextures(1, &tourTexture);
    SDL_FreeSurface(tourImg);
}*/

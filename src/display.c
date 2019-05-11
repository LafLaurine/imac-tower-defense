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

// A TERMINER : PAS IDEE DES COORDONNEES DU MONSTRE
int display_monster(GLuint* monster, List_Monster* list_monster) {

	//Vérifie qu'il existe
	if(monster != NULL && list_monster != NULL) {
	
		//Création d'un pointeur monstre temporaire pour parcourir la liste de monstres
		Monster *tmp = list_monster->m_last;

		//Parcours la liste de monstres
		while(tmp != NULL){

			int sprite;
			//Affecte un nb différent en fonction des différents types
			if(tmp->type == BACTERY)
				sprite = 0;
			else if(tmp->type == VIRUS) 
				sprite = 1;
			
			/*glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, *monster);
		
				glPushMatrix();
					glBegin(GL_QUADS);
					
					glEnd();
				glPopMatrix();

			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);*/

		}
	}
	else {
		printf("Can't display monster\n");
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
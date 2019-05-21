#include <stdlib.h>
#include <stdio.h>
/*
void writeString(int x, int y,  char* s) {

		char* c;
		
		// Positionne le premier caractère de la chaîne
		glRasterPos2f(x, y);
		for (c = s; *c != '\0'; c++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Affiche chaque caractère de la chaîne

		// Réinitialise la position du premier caractère de la chaîne
		glRasterPos2f(0, 0);
}
*/

int is_intersect(float x1, float y1, float x2, float y2, float radius){
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < radius*radius*4;
}
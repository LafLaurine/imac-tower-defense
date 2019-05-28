#include "../include/common.h"

int is_intersect(float x1, float y1, float x2, float y2, float r1, float r2){
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < (r1+r2)*(r1+r2);
}

int square_intersect_circle(float x1, float x2, float y1, float y2, int size_1, int size_2){
    if(x1 + (size_1 + size_2) >= x2 && x1 - (size_1 + size_2) <= x2 && y1 + (size_1 + size_2) >= y2 && y1 - (size_1 + size_2) <= y2){
        return 1;
    }else{
        return 0;
    }
}

int square_intersect_square(float x1, float x2, float y1, float y2, int size_1, int size_2){
    if(x1 + (size_1 + size_2) >= x2 && x1 - (size_1 + size_2) <= x2 && y1 + (size_1 + size_2) >= y2 && y1 - (size_1 + size_2) <= y2){
        return 1;
    }else{
        return 0;
    }
}

void vBitmapOutput(int x, int y, char *string, void *font)
{
	int len,i; // len donne la longueur de la chaîne de caractères

	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
	}
	// Réinitialise la position du premier caractère de la chaîne
	glRasterPos2f(0, 0);
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font)
{
	char *p;

	glPushMatrix();	
	glTranslatef(x, y, 0); // Positionne le premier caractère de la chaîne
	for (p = string; *p; p++) 
		glutStrokeCharacter(font, *p); // Affiche chaque caractère de la chaîne
	glPopMatrix();
}
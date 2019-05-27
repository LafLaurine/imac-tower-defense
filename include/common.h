#ifndef COMMON_H
#define COMMON_H
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef enum {
	FONT_24,	/*Taille 24 */
	FONT_32,	/*Taille 32 */
	FONT_48,	/*Taille 48 */
	MAX_FONTS	/*nombre max de polices */
} FONT_SIZE;

typedef struct {
	unsigned int id;	/*identifiant */
	unsigned int type;	
    char * text;
	GLuint tex[1];		/* texture */
	float xPos;	
    float yPos;	
	float xSize;	
    float ySize;	/* taille */
	SDL_Color color;	/* Couleur  */
	TTF_Font* font;		/* Police */
} Text;


TTF_Font *fonts[MAX_FONTS];

int is_intersect(float x1, float y1, float x2, float y2, float r1, float r2);
int square_intersect_circle(float x1, float x2, float y1, float y2, int size_1, int size_2);
int square_intersect_square(float x1, float x2, float y1, float y2, int size_1, int size_2);
void init_text();
void free_text();

#endif

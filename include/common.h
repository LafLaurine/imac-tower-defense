#ifndef COMMON_H
#define COMMON_H
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define FONT "bitmap"


int is_intersect(float x1, float y1, float x2, float y2, float radius);
int square_intersect_circle(float x1, float x2, float y1, float y2, int size_1, int size_2);
int square_intersect_square(float x1, float x2, float y1, float y2, int size_1, int size_2);

TTF_Font* loadFont(const char* fontName, int size);
void initFont(TTF_Font* font, SDL_Surface* texte);
#endif

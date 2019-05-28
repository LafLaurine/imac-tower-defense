#ifndef COMMON_H
#define COMMON_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

int is_intersect(float x1, float y1, float x2, float y2, float r1, float r2);
int square_intersect_circle(float x1, float x2, float y1, float y2, int size_1, int size_2);
int square_intersect_square(float x1, float x2, float y1, float y2, int size_1, int size_2);
void vBitmapOutput(int x, int y, char *string, void *font);
void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);
void scoredisplay(int posx, int posy, int posz, int space_char, int scorevar);

#endif

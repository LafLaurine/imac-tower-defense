#ifndef COMMON_H
#define COMMON_H
#include <GL/glut.h>
#include <string.h>

#include <string.h>
#include <GL/gl.h>
#include <GL/glut.h>

int is_intersect(float x1, float y1, float x2, float y2, float r1, float r2);
void vBitmapOutput(int x, int y, char *string, void *font);

#endif
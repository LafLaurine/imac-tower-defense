#ifndef IMG_H
#define IMG_H
#include<stdlib.h>
#include <string.h>
#include<stdio.h>
#include <stdbool.h>
#include "../include/pixel.h"
#include <ctype.h>

typedef struct Image {
	int width;
	int height;
	Pixel *rvb;
} Image;


void errorMsg(char *message);
void readPPMHeader(FILE* fp, int *w, int*h);
int allocate(Image *newImg, int width, int height);
void clear(Image *img);
int imageRead(Image *image, char *filename);
#endif
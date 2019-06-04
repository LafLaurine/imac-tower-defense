#ifndef IMG_H
#define IMG_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct Image {
	int width;
	int height;
	char *path;
	unsigned char *pixelData;
} Image;


// Read the header of a PPM file
Image* readPPMHeader(FILE* fp, int *w, int*h);
// Free memory
void free_image(Image *img);
// Read an image
Image* read_image(char *filename);

#endif
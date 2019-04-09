#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/image.h"

Image * initializeImage(FILE *i){
	Image *image;
	char format[2];
	int height;
	int width;

	// Read image file parameters
	fscanf(i,"%s\n", format);
	fscanf(i,"%d", &width);
	fscanf(i,"%d\n", &height);

	// Allocate enough space for the image
	image = malloc(sizeof(Image) + 3*height*width*sizeof(unsigned char));
	if (image == NULL) {
		fprintf(stderr, "Not enough memory!\n");
		exit(1);
	}

	// Read image file parameters
	strcpy(image->format, format);
	fscanf(i, "%d\n", &image->maxValue);
	image->height = height;
	image->width = width;

	return image;
}
void free_image (Image* image) {
	if(image != NULL) {
	    image->width  = 0;
	    image->height = 0;
		free(image);
	}
}
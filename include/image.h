#ifndef IMAGE_H
#define IMAGE_H

typedef struct Image {
	char format[2];
	unsigned int height;
	unsigned int width;
	int maxValue;
} Image;

//Ouvrir et stocker une image
Image *initializeImage(FILE *i);
//Supprimer une image
void free_image (Image* image);
#endif
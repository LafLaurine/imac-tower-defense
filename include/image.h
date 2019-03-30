#ifndef IMAGE_H
#define IMAGE_H

typedef struct Image {
	//chemin vers img
	char* path;
	char format[2];
	unsigned int height;
	unsigned int width;
	int maxValue;
} Image;

//Ouvrir et stocker une image
int read_image(Image*, char*);
//Supprimer une image
void free_image (Image*);
#endif
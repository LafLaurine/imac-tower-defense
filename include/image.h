#ifndef IMG_H
#define IMG_H


typedef struct Image {
	int width;
	int height;
	char * path;
} Image;


void errorMsg(char *message);
void readPPMHeader(FILE* fp, int *w, int*h);
int allocate(Image *newImg, int width, int height);
void free_image(Image *img);
int read_image(Image *image, char *filename);
#endif
#ifndef IMG_H
#define IMG_H


typedef struct Image {
	int width;
	int height;
	char *path;
	unsigned char pixelData[];
} Image;


void errorMsg(char *message);
Image* readPPMHeader(FILE* fp, int *w, int*h);
void free_image(Image *img);
Image* read_image(char *filename);
#endif
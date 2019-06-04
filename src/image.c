#include "../include/image.h"

Image* readPPMHeader(FILE* fp, int *w, int *h) {
	char ch;
	int maxval;

	// Check the PPM type
	if(fscanf(fp, "P%c\n",&ch)!=1 || ch!='3') {
		printf("Not PPM raw format\n");
		exit(EXIT_FAILURE);
	}

	// Check if there is comments
	ch = getc(fp);
	while(ch=='#') {
		do {
			ch=getc(fp);
		}
		while(ch!='\n');
		ch = getc(fp);
	}

	// Check if the following elements are digital or not
	if (!isdigit(ch)) {
		printf("Can't read header\n");
		exit(EXIT_FAILURE);
	}

	ungetc(ch,fp);
	if(fscanf(fp, "%d %d %d",w,h,&maxval) != 3) {
		printf("No width / height / maxval\n");
		exit(EXIT_FAILURE);
	}

	if(maxval!=255)	{
		printf("Not colored image\n");
		exit(EXIT_FAILURE);
	}

	Image *image = malloc(sizeof(Image));
	image->pixelData = malloc(3**h**w*sizeof(unsigned char)); //penser a convertir si bug sur ordi de la fac
	unsigned char* data = (unsigned char*) image->pixelData;
	
	for (int i=0; i<*w**h*3; i++) {
		if (fscanf(fp, "%hhu", data+i) != 1) {
			printf("Cannot read PPM : Invalid rgb component\n");
			exit(EXIT_FAILURE);
		}
	}

	return image;
}

Image* read_image(char *filename) {
	int width;
	int height;
	FILE *fp = fopen(filename, "rb");

	if (!fp) {
		printf("Cannot open file for reading\n");
		exit(EXIT_FAILURE);
	}

	Image* image = readPPMHeader(fp, &width, &height);

	if (width<=0 || height <=0) {
		printf("Negative size\n");
		exit(EXIT_FAILURE);
	}

	// Memory allocation
	if(!image) {
		printf("Not enough memory\n");
		exit(EXIT_FAILURE);
	}

	// Affect values to the structure
	image->width = width;
	image->height = height;

 	fclose(fp);
 	return image;
}

void free_image(Image *img) {
	// If structure is not empty
	if (img!=NULL) {
		img->width = 0;
		img->height = 0;
		free(img->path);
		free(img);
	}
}

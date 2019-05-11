#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/image.h"

//Handle error messages
void errorMsg(char *message)
{
	fprintf(stderr, "PPM : %s\n", message);
	exit(1);
}

//Read the header of a PPM file
Image* readPPMHeader(FILE* fp, int *w, int *h)
{
	char ch;
	int maxval;

	//check the PPM type
	if(fscanf(fp, "P%c\n",&ch)!=1 || ch!='3')
	{
		errorMsg("Not PPM raw format");
	}

	//check if there is comments
	ch = getc(fp);
	while(ch=='#')
	{
		do
		{
			ch=getc(fp);
		}
		while(ch!='\n');
		ch = getc(fp);
	}

	//check if the following elements are digital or not
	if (!isdigit(ch))
	{
		errorMsg("Can't read header");
	}

	ungetc(ch,fp);
	if(fscanf(fp, "%d%d%d\n",w,h,&maxval) != 3){
		errorMsg("No width / height / maxval");
	}

	if(maxval!=255)
	{
		errorMsg("Not colored image");
	}

	Image *image = malloc(sizeof(Image) + 3**h**w*sizeof(unsigned char));

	if(fread(image->pixelData, sizeof(unsigned char), *w**h*3, fp) == 0){
		errorMsg("Can't read data pixel");
		exit(EXIT_FAILURE);
	}

	//printf("%d\n", image->pixelData[]);

	return image;
}

//Read an image
Image* read_image(char *filename)
{
	int width;
	int height;
	FILE *fp = fopen(filename, "rb");

	if (!fp)
		errorMsg("Cannot open file for reading");
	Image* image = readPPMHeader(fp, &width, &height);

	if (width<=0 || height <=0)
	{
		errorMsg("Negative size");
	}

	//allocate memory
	
	if(!image)
	{
		errorMsg("Not enough memory");
		exit(EXIT_FAILURE);
	}

	//Affect values to the structure
	image->width = width;
	image->height = height;
	
	/*if(fread(image->pixelData, sizeof(unsigned char), width*height*3, fp) == 0){
		errorMsg("Can't read data pixel");
		exit(EXIT_FAILURE);
	}*/

 	fclose(fp);
 	return image;
}

//free memory
void free_image(Image *img)
{
	//if the structure is not empty
	if (img!=NULL)
	{
		img->width = 0;
		img->height = 0;
		free(img->path);
		free(img);
	}
	
}

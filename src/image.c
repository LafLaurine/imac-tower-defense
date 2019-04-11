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
void readPPMHeader(FILE* fp, int *w, int *h)
{
	char ch;
	int maxval;

	//check the PPM type
	if(fscanf(fp, "P%c\n",&ch)!=1 || ch!='6')
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
	fscanf(fp, "%d%d%d\n",w,h,&maxval);

	if(maxval!=255)
	{
		errorMsg("Not colored image");
	}
}

int allocate(Image *newImg, int width, int height)
{
	if (width<=0 || height <=0)
	{
		errorMsg("Negative size");
	}

	//rvb point to Pixel structure 
	//allocate memory
	newImg = malloc(sizeof(Image) + 3*height*width*sizeof(unsigned char));

	if(!newImg)
	{
		errorMsg("Not enough memory");
		return EXIT_FAILURE;
	}

	//Affect values to the structure
	newImg->width = width;
	newImg->height = height;
	return EXIT_SUCCESS;
}

//Read an image
int read_image(Image *image, char *filename)
{
	int width;
	int height;
	FILE  *fp = fopen(filename, "rb");
	if (!fp)
		errorMsg("Cannot open file for reading");
	readPPMHeader(fp, &width, &height);
	allocate(image,width,height);  	
 	fclose(fp);
 	return EXIT_SUCCESS;
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

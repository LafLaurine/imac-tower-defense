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
}

//Read an image
int read_image(Image *image, char *filename)
{
	int width;
	int height;
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		errorMsg("Cannot open file for reading");
	readPPMHeader(fp, &width, &height);
	printf("%d\n",width);

	if (width<=0 || height <=0)
	{
		errorMsg("Negative size");
	}

	//rvb point to Pixel structure 
	//allocate memory
	image = malloc(sizeof(Image) + 3*height*width*sizeof(unsigned char));

	if(!image)
	{
		errorMsg("Not enough memory");
		return EXIT_FAILURE;
	}

	//Affect values to the structure
	image->width = width;
	image->height = height;
	printf("image width and height%d\n %d\n", image->width, image->height);
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/image.h"

int read_image(Image* load_img, char* image_name) {
    FILE* image = NULL;
	image = fopen(image_name, "r");
	int height;
	int width;
	int comment = 0;
	if(image == NULL) {
		fprintf(stderr, "Erreur : Impossible d'ouvrir l'image\n");
		return 0;
	}

    else {
		if(fscanf(image, "%c%c\n", &(load_img->format[0]),  &(load_img->format[1])) == 2){
            if(load_img->format[0] != 'P' || load_img->format[1] != '6'){
				fprintf(stderr, "Wrong format\n");
				return 0;
			}

            else {
            	while(comment < 1) {
            		//on recupère la hauteur et la largeur
            		width = fscanf(image, "%d\n", &(img->width));
            		height = fscanf(image, "%d\n", &(img->height));
            		if (width!= NULL && height !=NULL) {
            			comment = 1;
            		}

            		else if (comment == 0) {
            			char* letter;
						//parcours la ligne jusqu'à qu'il trouve '\n'
						do {
							if(fread(&letter,sizeof(char*),1,image)!=1)
								printf("erreur\n");
						}while(*letter != '\n');
            		}
            	}

            	if(fscanf(image, "%d\n", &(img->maxValue)) == 1){
				
					//vide buffer + ferme l'image
					fflush(image);
					fclose(image);

				}
				else {
					fprintf(stderr, "Wrong value\n");
					return 0;
				}
                
            }
        }

        else {
        	fprintf(stderr, "Not a good PPM image\n");
			return 0;
        }
    }

	return 1;
}

void free_image (Image* image) {
	//Si l'interface existe
	if (image != NULL) {
		free(image->path);
		free(image);
	}
}
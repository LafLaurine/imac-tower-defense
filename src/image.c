#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file/Image.h"

int read_image(Image* load_img, char* image_name) {
    FILE* image = NULL;
	image = fopen(image_name, "r");
	if(image == NULL) {
		fprintf(stderr, "Erreur : Impossible d'ouvrir l'image\n");
		return 0;
	}

    else {
		if(fscanf(image, "%c%c\n", &(load_img->format[0]),  &(load_img->format[1])) == 2){
            if(load_img->format[0] != 'P' || load_img->format[1] != '6'){
				fprintf(stderr, "Mauvais format\n");
				return 0;
			}

            else {
                
            }
        }
    }

    //faut qu'on vérifie le commentaire


}

void free_image (Image* image) {
	//Si l'interface existe
	if (image != NULL) {
		free(image->path);
		free(image);
	}
}
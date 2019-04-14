#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/map.h"

Map* init_map (char* path) {
	if(path != NULL) {
		//Alloue la memoire
		Map* map = malloc(sizeof(Map));
		if(map != NULL) {
			if(verificationMap(map, path) == 0) {
				fprintf(stderr, "Unvalid map\n");
				return NULL;
			} else {
				fprintf(stderr, "Valid map !\n");
				return map;
			}
		} else {
			fprintf(stderr, "Coudln't allocate the map\n");
			return NULL;
		}
	} else {
		fprintf(stderr, "Map not found\n");
		return NULL;
	}	
}

int verificationMap(Map* map, char* map_itd){ 
	FILE* itd = NULL;
	itd = fopen(map_itd, "r");	

	if(itd == NULL){
		fprintf(stderr, "Couldn't open file\n");
		return 0;
	} else {
		char* check_itd;
		if(fscanf(itd, "%s", check_itd) == 1) {
			//Vérifie qu'il s'agit bien de carte
			if(strcmp("carte", check_itd) == 0) {

				//Alloue de la mémoire pour une image
				Image* new_img = (Image*)malloc(sizeof(Image));
				char* path = (char*)malloc(50*sizeof(char));
					
				//Récupère le chemin vers l'image ppm
				if(fscanf(itd, "%s\n", path) == 1){
					new_img->path = path;
					read_image(new_img, new_img->path);
					map->img = new_img;	

					//Récupère chemin
					char* test;
					if(fscanf(itd, "%s", test) == 1) {
						//Vérifie qu'il s'agit bien du chemin
						if(strcmp("chemin", test) == 0) {
							int r, v, b;
							//Récupère la couleur du chemin
							if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
								(map->path).r = r/255.0;
								(map->path).g = v/255.0;
								(map->path).b = b/255.0;
							}
						}
					}
				}
			}	
		}
	}
	return 1;
}

//si la couleur ne correspond pas à l'image, on doit la changer pour bien la mettre à niveau : pour noeud, construct, chemin, in et out. 
//Il faut trouver comment généraliser le truc car map->path ne change que pour le chemin. Pour ça il faut aussi modif valeur des px puisque pas tous même couleur
int change_path_color(Image* img, unsigned char* pixels, Map* map) {

	int i, j;

	// On parcourt les lignes du tableau
	for(i=0; i<(img->height); i++) {

		// puis on parcourt les colonnes du tableau
		for(j=0; j<(img->width); j++) {
			
			//On vérifie la couleur
			if(pixels[i*(img->height)*3+j*3] == 255 && pixels[i*(img->width)*3+j*3+1] == 255 && pixels[i*(img->width)*3+j*3+2] == 255){

				//Change de couleur
				pixels[i*(img->width)*3+j*3] = ((map->path).r)*255;
				pixels[i*(img->width)*3+j*3+1] = ((map->path).g)*255;
				pixels[i*(img->width)*3+j*3+2] = ((map->path).b)*255;
			}
		}
	}

	return 1;

}

void free_map (Map* map) {
	//Si la map existe
	if (map != NULL) {
		free(map);
	}
}
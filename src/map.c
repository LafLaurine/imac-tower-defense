#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file/Map.h"

int verificationMap(Map* map, char* map_itd){ 

	FILE* itd = NULL;
	itd = fopen(map_itd, "r");	

	if(itd == NULL){
		fprintf(stderr, "Couldn't open file\n");
		return 0;
	}
	else{
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


Map* init_map (char* path) {
	if(path != NULL) {
	//Alloue la memoire
		Map* map = malloc(sizeof(Map));
		if(map != NULL) {
			if(verif_map(map, path) == 0) {
				fprintf(stderr, "Unvalid map\n");
				return NULL;
			}
			return map;

		}
		else {
			fprintf(stderr, "Coudln't allocate the map\n");
			return NULL;
		}

	}
	else {
		fprintf(stderr, "Map not found\n");
		return NULL;
	}
	
	return 1;	

}
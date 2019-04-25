#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/map.h"

Map* init_map (char* path) {
	if(path != NULL) {
		//Alloue la memoire
		Map* map = malloc(sizeof(Map));
		if(map != NULL) {
			if(map_verification(map, path) == 0) {
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

int map_verification(Map* map, char* map_itd){ 
	FILE* itd = NULL;
	itd = fopen(map_itd, "r");	

	if(itd == NULL){
		fprintf(stderr, "Couldn't open file\n");
		return 0;
	} else {
		char* check_itd = (char*)malloc(20*sizeof(char));
		if(fscanf(itd, "%s", check_itd) == 1) {
			if(strcmp("@ITD", check_itd) == 0){
		
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
						if(fscanf(itd, "%s", check_itd) == 1) {
							//Vérifie qu'il s'agit bien du chemin
							if(strcmp("chemin", check_itd) == 0) {
								int r, v, b;
								//Récupère la couleur du chemin
								if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
									(map->path).r = r/255.0;
									(map->path).g = v/255.0;
							 		(map->path).b = b/255.0;
								}
							}
						}

						if(fscanf(itd, "%s", check_itd) == 1) {
							//Vérifie qu'il s'agit bien du chemin
							if(strcmp("noeud", check_itd) == 0) {
								int r, v, b;
								//Récupère la couleur du chemin
								if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
									(map->node).r = r/255.0;
									(map->node).g = v/255.0;
									(map->node).b = b/255.0;
								}
							}
						}

						if(fscanf(itd, "%s", check_itd) == 1) {
							//Vérifie qu'il s'agit bien du chemin
							if(strcmp("construct", check_itd) == 0) {
								int r, v, b;
								//Récupère la couleur du chemin
								if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
									List_Node* list_pixels = new_List_Node();
									map->list_pixels = list_pixels;
									(map->construct).r = r/255.0;
									(map->construct).g = v/255.0;
									(map->construct).b = b/255.0;
								}
							}
						}

						if(fscanf(itd, "%s", check_itd) == 1) {
							//Vérifie qu'il s'agit bien du chemin
							if(strcmp("in", check_itd) == 0) {
								int r, v, b;
								//Récupère la couleur du chemin
								if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
									(map->in).r = r/255.0;
									(map->in).g = v/255.0;
									(map->in).b = b/255.0;
								}
							}
						}

						if(fscanf(itd, "%s", check_itd) == 1) {
							//Vérifie qu'il s'agit bien du chemin
							if(strcmp("out", check_itd) == 0) {
								int r, v, b;
								//Récupère la couleur du chemin
								if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
									(map->out).r = r/255.0;
									(map->out).g = v/255.0;
									(map->out).b = b/255.0;
								}
							}
						}

						if(fscanf(itd, "%d\n", &(map->number_node)) == 1){
							int i, x, y;
							//Création d'une nouvelle liste de noeuds
							map->list_node = new_List_Node();
							if(map->list_node != NULL){
								for(i=0; i < (map->number_node); i++){
								//Récupére les coordonnées
									if(fscanf(itd, "%d %d\n", &x, &y) == 2){
									//Vérifie que le noeud se trouve dans l'image
										if(x <= map->img->width && x >= 0 && y <= map->img->height && y >= 0){
											//Vérifie que le noeud à bien été ajouté à la liste de noeud
											if(add_node(map->list_node, x, y) != 1) {
												fprintf(stderr, "Not integer");
												return 0;
											}
										}
										else{
											fprintf(stderr, "Cannot find node on map");
											return 0;
										}
									}
									else {
										fprintf(stderr, "Wrong coordonate");
										return 0;
									}
								}
							}
						}
						else {
							fprintf(stderr, "Not node number");
							return 0;
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
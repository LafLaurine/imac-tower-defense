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
			} 
			fprintf(stderr, "Valid map !\n");
			return map;
		} else {
			fprintf(stderr, "Coudln't allocate the map\n");
			return NULL;
		}
	} else {
		fprintf(stderr, "Map not found\n");
		return NULL;
	}	
	return NULL;
}


int map_verification(Map* map, char* map_itd){ 
	FILE* itd = NULL;
	itd = fopen(map_itd, "r");	

	if(itd == NULL){
		fprintf(stderr, "Couldn't open file\n");
		return 0;
	} else {

		// PREMIERE LIGNE : fichier ITD
		char* type = (char*)malloc(20*sizeof(char));
		char ligne[100];
		int numb;

		if((fgets(ligne, 99, itd) == NULL) && (sscanf(ligne,"%s %d", type, &numb) != 2)){
			printf("%s", "Unreadable file (at : itd file recognition)");
			exit(EXIT_FAILURE);
		}


		// DEUXIEME LIGNE : commentaires
		int comments;
		comments = getc(itd);
		while (comments == '#'){
			while(getc(itd) != '\n');
			comments = getc(itd);
		}
		ungetc(comments, itd);


		// TROISIEME LIGNE : chemin carte
		//Alloue de la mémoire pour une image
		char* carte = (char*)malloc(sizeof(char));
		char* path = (char*)malloc(sizeof(char));

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %s", carte, path) == 2)){
				Image* new_img = (Image*)malloc(sizeof(Image));
				new_img = read_image(path);
				new_img->path = path;
				map->img = new_img;
		} else {
			printf("%s", "Unreadable file (at : map path)");
			exit(EXIT_FAILURE);
		}


		// QUATRIEME LIGNE : energie
		if(fgets(ligne, 99, itd) == NULL){
			printf("%s", "Unreadable file (at : energie)");
			exit(EXIT_FAILURE);
		}


		// CINQUIEME LIGNE : couleur chemin
		char* chemin = (char*)malloc(sizeof(char));
		int chemin_r; int chemin_g; int chemin_b;

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %d %d %d", chemin, &chemin_r, &chemin_g, &chemin_b) == 4)){
			if(chemin_r < 0 || chemin_r > 255) {
				fprintf(stderr, "Red value from path out of range\n");
				exit(EXIT_FAILURE);
			}
			if(chemin_g < 0 || chemin_g > 255) {
				fprintf(stderr, "Green value from path out of range\n");
				exit(EXIT_FAILURE);
			}
			if(chemin_b < 0 || chemin_b > 255) {
				fprintf(stderr, "Blue value from path out of range\n");
				exit(EXIT_FAILURE);
			}
			(map->path).r = chemin_r;
			(map->path).g = chemin_g;
			(map->path).b = chemin_b;
		} else {
			printf("%s", "Unreadable file (at : path color)");
			exit(EXIT_FAILURE);
		}


		// SIXIEME LIGNE : couleur noeud
		char* noeud = (char*)malloc(20*sizeof(char));
		int noeud_r; int noeud_g; int noeud_b;

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %d %d %d", noeud, &noeud_r, &noeud_g, &noeud_b) == 4)){
			if(noeud_r < 0 || noeud_r > 255) {
				fprintf(stderr, "Red value from node out of range\n");
				exit(EXIT_FAILURE);
			}
			if(noeud_g < 0 || noeud_g > 255) {
				fprintf(stderr, "Green value from node out of range\n");
				exit(EXIT_FAILURE);
			}
			if(noeud_b < 0 || noeud_b > 255) {
				fprintf(stderr, "Blue value from node out of range\n");
				exit(EXIT_FAILURE);
			}
			(map->node).r = noeud_r;
			(map->node).g = noeud_g;
			(map->node).b = noeud_b;
		} else {
			printf("%s", "Unreadable file (at : node color)");
			exit(EXIT_FAILURE);
		}


		// SIXIEME LIGNE : couleur construct
		char* construct = (char*)malloc(20*sizeof(char));
		int construct_r; int construct_g; int construct_b;

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %d %d %d", construct, &construct_r, &construct_g, &construct_b) == 4)){
			List_Node* list_pixels = new_List_Node();
			map->list_pixels = list_pixels;
			if(construct_r < 0 || construct_r > 255) {
				fprintf(stderr, "Red value from construct out of range\n");
				exit(EXIT_FAILURE);
			}
			if(construct_g < 0 || construct_g > 255) {
				fprintf(stderr, "Green value from construct out of range\n");
				exit(EXIT_FAILURE);
			}
			if(construct_b < 0 || construct_b > 255) {
				fprintf(stderr, "Blue value from construct out of range\n");
				exit(EXIT_FAILURE);
			}
			(map->construct).r = construct_r;
			(map->construct).g = construct_g;
			(map->construct).b = construct_b;
		} else {
			printf("%s", "Unreadable file (at : construct color)");
			exit(EXIT_FAILURE);
		}


		// SEPTIEME LIGNE : couleur in
		char* in = (char*)malloc(20*sizeof(char));
		int in_r; int in_g; int in_b;

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %d %d %d", in, &in_r, &in_g, &in_b) == 4)){
			if(in_r < 0 || in_r > 255) {
				fprintf(stderr, "Red value from in out of range\n");
				exit(EXIT_FAILURE);
			}
			if(in_g < 0 || in_g > 255) {
				fprintf(stderr, "Green value from in out of range\n");
				exit(EXIT_FAILURE);
			}
			if(in_b < 0 || in_b > 255) {
				fprintf(stderr, "Blue value from in out of range\n");
				exit(EXIT_FAILURE);
			}
			(map->in).r = in_r;
			(map->in).g = in_g;
			(map->in).b = in_b;
		} else {
			printf("%s", "Unreadable file (at : in colo)");
			exit(EXIT_FAILURE);
		}


		// HUITIEME LIGNE : couleur out
		char* out = (char*)malloc(20*sizeof(char));
		int out_r; int out_g; int out_b;

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %d %d %d", out, &out_r, &out_g, &out_b) == 4)){
			if(out_r < 0 || out_r > 255) {
				fprintf(stderr, "Red value from out, out of range\n");
				exit(EXIT_FAILURE);
			}
			if(out_g < 0 || out_g > 255) {
				fprintf(stderr, "Green value from out, out of range\n");
				exit(EXIT_FAILURE);
			}
			if(out_b < 0 || out_b > 255) {
				fprintf(stderr, "Blue value from out, out of range\n");
				exit(EXIT_FAILURE);
			}	
			(map->out).r = out_r;
			(map->out).g = out_g;
			(map->out).b = out_b;
		} else {
			printf("%s", "Unreadable file (at : out color)");
			exit(EXIT_FAILURE);
		}


		// NEUVIEME LIGNE : nombre noeuds
		int nb_node;

		if( (fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%d", &nb_node) == 1) ){
			map->number_node = nb_node;
		} else {
			printf("%s", "Unreadable file (at : node number)");
			exit(EXIT_FAILURE);
		}

		// DERNIERES LIGNES : infos noeuds
		int node_indice;
		int node_type;
		int node_x;
		int node_y;
		int compteur = 0;
		// + int successeurs à ajouter

		while(fgets(ligne, 99, itd) != NULL){
				map->list_node = new_List_Node();
				if(map->list_node != NULL){
					//Récupére les coordonnées
					if(sscanf(ligne,"%d %d %d %d", &node_indice, &node_type, &node_x, &node_y) == 4){
					//Vérifie que le noeud se trouve dans l'image
						if(node_x <= map->img->width && node_x >= 0 && node_y <= map->img->height && node_y >= 0){
						//Vérifie que le noeud à bien été ajouté à la liste de noeud
							if(add_node(map->list_node, node_x, node_y) != 1) {
								fprintf(stderr, "Nodes not added");
								exit(EXIT_FAILURE);
							}
						} else{
							fprintf(stderr, "Cannot find node on map");
							exit(EXIT_FAILURE);
						}
					}
					else {
						printf("%s", "Unreadable file (at : node)");
						exit(EXIT_FAILURE);
					}	
				}
			compteur++;
		}

		
		if(compteur > nb_node || compteur < nb_node){
			printf("%s", "pas le bon nombre de node");
			exit(EXIT_FAILURE);
		}

		fflush(itd);
		fclose(itd);
}
	return 1;
}

//si la couleur ne correspond pas à l'image, on doit la changer pour bien la mettre à niveau : pour noeud, construct, chemin, in et out. 
//Il faut trouver comment généraliser le truc car map->path ne change que pour le chemin. Pour ça il faut aussi modif valeur des px puisque pas tous même couleur
int change_path_color(Image* img, unsigned char* pixels, Map* map, Color3f path, float r, float g, float b) {

	int i, j;

	// On parcourt les lignes du tableau
	for(i=0; i<(img->height); i++) {

		// puis on parcourt les colonnes du tableau
		for(j=0; j<(img->width); j++) {
			
			//On vérifie la couleur
			if(pixels[i*(img->height)*3+j*3] == r && pixels[i*(img->width)*3+j*3+1] == g && pixels[i*(img->width)*3+j*3+2] == b){

				//Change de couleur
				pixels[i*(img->width)*3+j*3] = ((map->path).r)*255;
				pixels[i*(img->width)*3+j*3+1] = ((map->path).g)*255;
				pixels[i*(img->width)*3+j*3+2] = ((map->path).b)*255;
			}
		}
	}

	return 1;
}

int check_segment(int x1, int y1, int x2, int y2, Map* map){
	int x, y;
	float erreur = -0.5;
	float x_err, y_err;

	x = x1;
	y = y1;

	x_err = (y2 - y1) / (x2 - x1);
	y_err = -1;

	while(x<x2){
		x++;
		if(check_pixel(x, y, map) == 0){
			printf("%s", "Wrong pixel color\n");
			exit(EXIT_FAILURE);
		}
		erreur += x_err;

		if(erreur > 0){
			y++;
			erreur += y_err;
		}
	}
	printf("%s", "Good segment, good path !\n");
	return 1;
}

int check_pixel(int x, int y, Map* map){
	
	printf("Rouge du pixel : %d\n", map->img->pixelData[1]);
	//printf("%d", map->img->pixelData[y*(map->img->height)*3+x*3+1]); tab[hauteurImage*largeurImage*3 + 3x + c]
	//printf("%d", map->img->pixelData[y*(map->img->height)*3+x*3]);
	if(map->img->pixelData[y*(map->img->height)*3+x*3] == map->path.r){
		if(map->img->pixelData[y*(map->img->height)*3+x*3+1] == map->path.g){
			if(map->img->pixelData[y*(map->img->height)*3+x*3+2] == map->path.b){
				return 1;
			}
		}
	}
	return 0;
}

void free_map(Map* map) {
	//Si la map existe
	if (map != NULL) {
		free(map->img);
		free_all_node(map->list_pixels);
		free_all_node(map->list_node);
		free(map);
	}
}

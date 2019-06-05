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
			map->path = change_color(chemin_r,chemin_g,chemin_b);
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
			map->node = change_color(noeud_r,noeud_g,noeud_b);
		} else {
			printf("%s", "Unreadable file (at : node color)");
			exit(EXIT_FAILURE);
		}


		// SIXIEME LIGNE : couleur construct
		char* construct = (char*)malloc(20*sizeof(char));
		int construct_r; int construct_g; int construct_b;

		if((fgets(ligne, 99, itd) != NULL) && (sscanf(ligne,"%s %d %d %d", construct, &construct_r, &construct_g, &construct_b) == 4)){
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
			map->construct = change_color(construct_r,construct_g,construct_b);
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
			map->in = change_color(in_r,in_g,in_b);
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
			else {
				map->out = change_color(out_r,out_g,out_b);
			}
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
		float node_x;
		float node_y;
		int compteur = 0;
		int *successors = malloc(sizeof(int*));
		int inBool = 0; //boolean
		int outBool = 0;
		
		map->list_node = new_List_Node();
		while(fgets(ligne, 99, itd) != NULL){
				
				if(map->list_node != NULL){
					
					//Récupére les coordonnées
					char *token;
					float ftoken;
					int itoken;
					int i = 0;
					int j = 0;
					token = strtok(ligne, " ");

					while( token != NULL ) {
						ftoken = atof(token);
						itoken = atoi(token);
						if(i == 0){
							node_indice = itoken;
							if(inBool == 0 && strcmp(token, "0")){
								inBool = 1;
							}

							if(outBool == 0 && strcmp(token, "1")){
								outBool = 1;
							}
						} else if(i == 1){
							node_type = itoken;
						} else if(i == 2){
							node_x = ftoken;
						} else if(i == 3){
							node_y = ftoken;
						} else {
							successors[j] = itoken;	
							j++;
						}
    
      					token = strtok(NULL, " ");
						i++;
					}

					//Vérifie que le noeud se trouve dans l'image
					if(node_x <= map->img->width && node_x >= 0 && node_y <= map->img->height && node_y >= 0){
							
						//Vérifie que le noeud à bien été ajouté à la liste de noeud
						if(create_node(node_type, node_x, node_y, successors, map->list_node, node_indice) != 1) {
							fprintf(stderr, "Nodes not added");
							exit(EXIT_FAILURE);
						}
					} else{
						fprintf(stderr, "Cannot find node on map");
						exit(EXIT_FAILURE);
					}

				}
			compteur++;
		}
		
		if(inBool == 0 || outBool == 0){
			fprintf(stderr, "Node in or node out inexistant");
			exit(EXIT_FAILURE);	
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

Color3f change_color(float r, float g, float b){

	Color3f colors;
	colors.r = r;
	colors.g = g;
	colors.b = b;

	return colors;

}

//bressenham
int check_segment_X(int x1, int y1, int x2, int y2, Map* map){
	int x, y;
	float erreur = -0.5;
	float x_err, y_err;
	int step = 1;
	Color3f color = map->node;
	x = x1;
	y = y1;
	x_err = (y2 - y1) / (x2 - x1);
	y_err = -1;

	while(x<x2){
		x++;

		if(check_pixel(x, y, map, color) == 0){
			if (color.r == map->node.r)
			{
				color = map->path;
				step = 2;
			} else {
				color = map->node;
				step = 3;
			}
		}
		erreur += x_err;
		//printf("erreur : %f, erreur de X: %f\n", erreur, x_err);

		if(erreur > 0){
			y++;
			erreur += y_err;
		}
	}

	if(step != 3){
		printf("%s", "Not a good path\n");
		exit(EXIT_FAILURE);
	}

	printf("%s", "Good segment, good path !\n");
	return 1;
}

// Pas sur que ça fonctionne
int check_segment_Y(int x1, int y1, int x2, int y2, Map* map){
	int x, y;
	float erreur = -0.5;
	float x_err, y_err;
	int step = 1;
	Color3f color = map->node;

	x = x1;
	y = y1;
	x_err = -1;
	y_err = (x2 - x1) / (y2 - y1);

	while(y<y2){
		y++;

		if(check_pixel(x, y, map, color) == 0){
			if (color.r == map->node.r)
			{
				color = map->path;
				step = 2;
			} else {
				color = map->node;
				step = 3;
			}
		}
		erreur += y_err;
		//printf("erreur : %f, erreur de X: %f\n", erreur, x_err);

		if(erreur > 0){
			x++;
			erreur += x_err;
		}
	}

	if(step != 3){
		printf("%s", "Not a good path\n");
		exit(EXIT_FAILURE);
	}

	printf("%s", "Good segment, good path !\n");
	return 1;
}


int check_pixel(int x, int y, Map* map, Color3f color){
	//printf("Rouge du pixel : %u, coordonnee x: %d et y: %d\n",map->img->pixelData[(y*(map->img->width)+x)*3], x, y);
	
	if(map->img->pixelData[(y*(map->img->width)+x)*3] == map->path.r){
		if(map->img->pixelData[(y*(map->img->width)+x)*3+1] == map->path.g){
			if(map->img->pixelData[(y*(map->img->width)+x)*3+2] == map->path.b){
				return 1;
			}
		}
	}
	return 0;
}


void init_djisksra(Map *map, int* tab_chemin) {
    //tableau des sommets + successeurs
    //tableau des valeurs (initalement ça doit être infini mais ici pour test on mets 10000)
    //tableau des sommets visités : initialement tous à -1 et passe à 0 quand visité + prédécesseurs
    int sommet[map->number_node];
    //value taille des number_node
    int value[map->number_node];
    //taille nombre noeud
    int visited[map->number_node];

    //initialisation value à 300
    //init visited tous à -1
    for(int i =0; i<map->number_node;i++) {
        value[i] = 300;
        visited[i] = -1;
        sommet[i] = -1;
    }

    sommet[0] = 0;
    visited[0] = 0;
    value[0] = 0;

    Node* tmp = map->list_node->head;
    sommet[tmp->indice]=tmp->indice;
    value[tmp->indice] = 0;

	printf("val sommet : %d", tmp->next->indice);
    //tant que pas noeud sorti
    // + boucle successeurs -> regarder si value = 300 et vistied = -1, on affecte value de là ou on se trouve en i et on ajoute +1
   	while(tmp->type != Out && tmp->next != NULL) {
        while(tmp->successors != NULL) {
			//chemin visite
			visited[tmp->indice] = 0;
		}


        tmp = tmp->next;
    }
}


void free_map(Map* map) {
	//Si la map existe
	if (map != NULL) {
		free(map->img);
/*		free_all_node(map->list_pixels);
		free_all_node(map->list_node);*/
		free(map);
	}
}

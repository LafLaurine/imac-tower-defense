#include "../include/map.h"

Map* init_map(char* path) {
	if(path != NULL) {
		// Allocate memory
		Map* map = malloc(sizeof(Map));

		if(map != NULL) {
			if(check_map(map, path) == 0) {
				fprintf(stderr, "Unvalid map\n");
				return NULL;
			}
			printf("Valid map !\n");
			return map;

		} else {
			printf("Couldn't allocate the map\n");
			return NULL;
		}
	} else {
		printf("Map not found\n");
		return NULL;
	}	
	return NULL;
}

int check_map(Map* map, char* map_itd){ 
	FILE* itd = NULL;
	itd = fopen(map_itd, "r");	

	if(itd == NULL){
		fprintf(stderr, "Couldn't open file\n");
		return 0;

	} else {

		// FIRST LINE : ITD file
		char* type = (char*)malloc(20*sizeof(char));
		char line[100];
		int numb;

		if((fgets(line, 99, itd) == NULL) && (sscanf(line,"%s %d", type, &numb) != 2)){
			printf("Unreadable file (at : itd file recognition)");
			exit(EXIT_FAILURE);
		}


		// SECOND LINE : comments
		int comments;
		comments = getc(itd);
		while (comments == '#'){
			while(getc(itd) != '\n');
			comments = getc(itd);
		}
		ungetc(comments, itd);


		// THIRD LINE : map path
		//Allocate memory for image
		char* carte = (char*)malloc(sizeof(char));
		char* path = (char*)malloc(sizeof(char));

		if((fgets(line, 99, itd) != NULL) && (sscanf(line,"%s %s", carte, path) == 2)){
			Image* new_img = (Image*)malloc(sizeof(Image));
			new_img = read_image(path);
			new_img->path = path;
			map->img = new_img;
		} else {
			printf("Unreadable file (at : map path)");
			exit(EXIT_FAILURE);
		}


		// FORTH LINE : energy
		if(fgets(line, 99, itd) == NULL){
			printf("Unreadable file (at : energie)");
			exit(EXIT_FAILURE);
		}


		// FITH LINE : path color
		char* chemin = (char*)malloc(sizeof(char));
		int chemin_r; int chemin_g; int chemin_b;

		if((fgets(line, 99, itd) != NULL) && (sscanf(line,"%s %d %d %d", chemin, &chemin_r, &chemin_g, &chemin_b) == 4)){
			if(chemin_r < 0 || chemin_r > 255) {
				printf("Red value from path out of range\n");
				exit(EXIT_FAILURE);
			}
			if(chemin_g < 0 || chemin_g > 255) {
				printf("Green value from path out of range\n");
				exit(EXIT_FAILURE);
			}
			if(chemin_b < 0 || chemin_b > 255) {
				printf("Blue value from path out of range\n");
				exit(EXIT_FAILURE);
			}
			map->path = change_color(chemin_r,chemin_g,chemin_b);

		} else {
			printf("Unreadable file (at : path color)");
			exit(EXIT_FAILURE);
		}


		// SIXTH LINE : node color
		char* node = (char*)malloc(20*sizeof(char));
		int node_r; int node_g; int node_b;

		if((fgets(line, 99, itd) != NULL) && (sscanf(line,"%s %d %d %d", node, &node_r, &node_g, &node_b) == 4)){
			if(node_r < 0 || node_r > 255) {
				printf("Red value from node out of range\n");
				exit(EXIT_FAILURE);
			}
			if(node_g < 0 || node_g > 255) {
				printf("Green value from node out of range\n");
				exit(EXIT_FAILURE);
			}
			if(node_b < 0 || node_b > 255) {
				printf("Blue value from node out of range\n");
				exit(EXIT_FAILURE);
			}
			map->node = change_color(node_r,node_g,node_b);

		} else {
			printf("Unreadable file (at : node color)");
			exit(EXIT_FAILURE);
		}


		// SEVENTH LINE : construct color
		char* construct = (char*)malloc(20*sizeof(char));
		int construct_r; int construct_g; int construct_b;

		if((fgets(line, 99, itd) != NULL) && (sscanf(line,"%s %d %d %d", construct, &construct_r, &construct_g, &construct_b) == 4)){
			if(construct_r < 0 || construct_r > 255) {
				printf("Red value from construct out of range\n");
				exit(EXIT_FAILURE);
			}
			if(construct_g < 0 || construct_g > 255) {
				printf("Green value from construct out of range\n");
				exit(EXIT_FAILURE);
			}
			if(construct_b < 0 || construct_b > 255) {
				printf("Blue value from construct out of range\n");
				exit(EXIT_FAILURE);
			}
			map->construct = change_color(construct_r, construct_g, construct_b);

		} else {
			printf("Unreadable file (at : construct color)\n");
			exit(EXIT_FAILURE);
		}


		// HEIGHT LINE : color in
		char* in = (char*)malloc(20*sizeof(char));
		int in_r; int in_g; int in_b;

		if((fgets(line, 99, itd) != NULL) && (sscanf(line,"%s %d %d %d", in, &in_r, &in_g, &in_b) == 4)){
			if(in_r < 0 || in_r > 255) {
				printf("Red value from in out of range\n");
				exit(EXIT_FAILURE);
			}
			if(in_g < 0 || in_g > 255) {
				printf("Green value from in out of range\n");
				exit(EXIT_FAILURE);
			}
			if(in_b < 0 || in_b > 255) {
				printf("Blue value from in out of range\n");
				exit(EXIT_FAILURE);
			}
			map->in = change_color(in_r, in_g, in_b);

		} else {
			printf("Unreadable file (at : in colo)\n");
			exit(EXIT_FAILURE);
		}


		// NINTH LINE : color out
		char* out = (char*)malloc(20*sizeof(char));
		int out_r; int out_g; int out_b;

		if((fgets(line, 99, itd) != NULL) && (sscanf(line,"%s %d %d %d", out, &out_r, &out_g, &out_b) == 4)){
			if(out_r < 0 || out_r > 255) {
				printf("Red value from out, out of range\n");
				exit(EXIT_FAILURE);
			}
			if(out_g < 0 || out_g > 255) {
				printf("Green value from out, out of range\n");
				exit(EXIT_FAILURE);
			}
			if(out_b < 0 || out_b > 255) {
				printf("Blue value from out, out of range\n");
				exit(EXIT_FAILURE);
			}
			else {
				map->out = change_color(out_r, out_g, out_b);
			}

		} else {
			printf("Unreadable file (at : out color)\n");
			exit(EXIT_FAILURE);
		}


		// TENTH LINE : nb node
		int nb_node;

		if( (fgets(line, 99, itd) != NULL) && (sscanf(line,"%d", &nb_node) == 1) ){
			map->number_node = nb_node;
		} else {
			printf("Unreadable file (at : node number)\n");
			exit(EXIT_FAILURE);
		}

		// LAST LINES : node information
		int node_index;
		int node_type;
		float node_x;
		float node_y;
		int compt = 0;
		int inBool = 0; //boolean
		int outBool = 0;
		
		map->list_node = new_List_Node();
		Node* previous = malloc(sizeof(Node));
		
		while(fgets(line, 99, itd) != NULL){
				if(map->list_node != NULL){
					
					// Get position
					char *token;
					float ftoken;
					int itoken;
					int i = 0;
					int j = 0;
					int *successors = malloc(sizeof(int*));
					int nb_successors = 0;
					token = strtok(line, " ");

					while( token != NULL ) {
						ftoken = atof(token);
						itoken = atoi(token);

						if(i == 0){
							node_index = itoken;
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
							nb_successors++;	
							j++;
						}
    
      					token = strtok(NULL, " ");
						i++;
					}

					// Check everynode are in the image
					if(node_x <= map->img->width && node_x >= 0 && node_y <= map->img->height && node_y >= 0){
						
						// BRESSENHAM : check every path is from one point to another
						if(map->list_node->head != NULL){
							if ((node_x - previous->x) != 0) {
								check_segment_X(previous->x, previous->y, node_x, node_y, map);
							} else {
								check_segment_Y(previous->x, previous->y, node_x, node_y, map);
							}
						}					
						
						// Check node is in node list
						previous = create_node(node_type, node_x, node_y, successors, nb_successors, map->list_node, node_index);
						if(previous == NULL) {
							printf("Nodes not added\n");
							exit(EXIT_FAILURE);
						}
					} else{
						printf("Cannot find node on map\n");
						exit(EXIT_FAILURE);
					}
				}
			compt++;
		}		
		
		if(inBool == 0 || outBool == 0){
			printf("Node in or node out inexistant");
			exit(EXIT_FAILURE);	
		}
		
		if(compt > nb_node || compt < nb_node){
			printf("Incorrect node number");
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

	while(x != x2) {
		if(x<x2) {
			x++;
		} else {
			x--;
		}

		if(check_pixel(x, y, map, color) == 0) {
			if (color.r != map->node.r) {
				color = map->path;
				step = 2;
			} else {
				color = map->node;
				step = 3;
			}
		}
		erreur += x_err;

		if(erreur > 0) {
			y++;
			erreur += y_err;
		}
	}

	if(step != 3) {
		printf("Not a good path\n");
		exit(EXIT_FAILURE);
	}

	printf("Good segment, good path !\n");
	return 1;
}

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

	while(y != y2){
		if(y<y2){
			y++;
		} else {
			y--;
		}

		if(check_pixel(x, y, map, color) == 0){
			if (color.r != map->node.r)
			{
				color = map->path;
				step = 2;
			} else {
				color = map->node;
				step = 3;
			}
		}
		erreur += y_err;

		if(erreur > 0){
			x++;
			erreur += x_err;
		}
	}

	if(step != 3){
		printf("Not a good path\n");
		exit(EXIT_FAILURE);
	}

	printf("Good segment, good path !\n");
	return 1;
}


int check_pixel(int x, int y, Map* map, Color3f color){
	if(map->img->pixelData[(y*(map->img->width)+x)*3] == map->path.r){
		if(map->img->pixelData[(y*(map->img->width)+x)*3+1] == map->path.g){
			if(map->img->pixelData[(y*(map->img->width)+x)*3+2] == map->path.b){
				return 1;
			}
		}
	}
	return 0;
}

Node* findNode(int index, Map map){
	Node* temp = map.list_node->head;

	while(temp != NULL) {
		if(index == temp->indice) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/* 
void init_djisksra(Map map, int* tab_path) {
    //tableau des sommets + successeurs
    //tableau des valeurs (initalement ça doit être infini mais ici pour test on mets 10000)
    //tableau des sommets visités : initialement tous à -1 et passe à 0 quand visité + prédécesseurs
    int sommet[map.number_node];
    //value taille des number_node
    int value[map.number_node];
    //taille nombre node
    int visited[map.number_node];

    //initialisation value à 300
    //init visited tous à -1
    for(int i=0; i < map.number_node; i++) {
        value[i] = 300;
        visited[i] = -1;
        sommet[i] = -1;
    }

    sommet[0] = 0;
    visited[0] = 0;
    value[0] = 0;

    Node* route = map.list_node->head;

    //tant que pas node sorti
    // + boucle successeurs -> regarder si value = 300 et vistied = -1, on affecte value de là ou on se trouve en i et on ajoute +1
   	while(route->type != Out && route->next != NULL) {
		Node *tmp = route;

		for(int c=0; c < tmp->nb_successors; c++){
			//chemin visite
			visited[route->indice] = 0;

			if(sommet[tmp->successors[c]] == -1 && value[tmp->successors[c]] != 255){
				if((value[tmp->indice]+1) < value[tmp->successors[c]]){
					sommet[tmp->successors[c]] = route->indice;
					value[tmp->successors[c]] = value[route->indice]+1;
				}
			}
			if(sommet[tmp->successors[c]] == -1){
				sommet[tmp->successors[c]] = route->indice;
				value[tmp->successors[c]] = value[route->indice]+1;
			}
			printf("sucessor C %d et route indice %d , compteur %d \n", tmp->successors[c], route->indice, c);
		}

		int min = 300;
		int indexMin = 0;

		for(int i=0; i<map.number_node; i++){
			if(visited[i] != 0 && value[i] != 300){
				if(value[i] < min){
					min = value[i];
					indexMin = i;
				}
			}
		}

		printf("index %d et valeur %d\n", indexMin, min);
		route->next = findNode(indexMin, map);
		route = route->next;
    }

	int sommet_index = 1;
	int compt = 0;

	while (sommet_index != 0) {
		tab_path[compt] = sommet_index;
		sommet_index = sommet[sommet_index];
		compt++;
	}

	tab_path[compt++] = sommet_index;
} */


void free_map(Map* map) {
	// If map exists
	if (map != NULL) {
		free(map->img);
		free_all_node(map->list_node);
		free(map);
	}
}

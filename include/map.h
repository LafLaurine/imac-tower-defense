#ifndef MAP_H
#define MAP_H

#include "colors.h"
#include "image.h"
#include "node.h"

typedef struct Map {

	//Image ppm
	Image* img;
	//couleur du chemin
	Color3f path;
	//couleur des noeuds
	Color3f node;
	//couleur à la zone constructible
	Color3f construct;
	//couleur clé de la zone d'entrée
	Color3f in;
	//couleur clé de la zone de sortie
	Color3f out;
	//Nombre de noeud
	unsigned int number_node;
	//Liste des noeuds
	List_Node* list_node;
	Node *list;

}Map;

//Initialisation de la carte
Map* init_map (char* path);
//Vérification de la carte
int map_verification(Map* map, char* map_itd);
//changer couleurs
Color3f change_color(float r, float g, float b);
//Check les chemins X
int check_segment_X(int x1, int y1, int x2, int y2, Map* map);
//Check les chemins Y
int check_segment_Y(int x1, int y1, int x2, int y2, Map* map);
//check les pixels
int check_pixel(int x, int y, Map* map, Color3f color);
void init_djisksra(Map *map, int* tab_chemin);
//Libere la carte
void free_map(Map* map);

#endif
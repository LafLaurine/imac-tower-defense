#ifndef MAP_H
#define MAP_H

#include "../include/colors.h"
#include "../include/image.h"
#include "../include/node.h"

typedef struct Map {

	//Image ppm
	Image* img;
	//couleur du chemin
	Color3f path;
	//couleur des noeuds
	Color3f node;
	//couleur à la zone constructible
	Color3f construct;
	//liste des pixels de zone constructible
	List_Node* list_pixels;
	//couleur clé de la zone d'entrée
	Color3f in;
	//couleur clé de la zone de sortie
	Color3f out;
	//Nombre de noeud
	int number_node;
	//energie
	int energie;
	//Liste des noeuds
	List_Node* list_node;

}Map;

//Initialisation de la carte
Map* init_map (char* path);
//Vérification de la carte
int verificationMap(Map* map, char* map_itd);
//Change couleur en fonction de l'image
int change_path_color(Image* img, unsigned char* pixels, Map* map);
//Libere la carte
void free_map (Map* map);

#endif
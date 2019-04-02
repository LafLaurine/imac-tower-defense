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
	//Liste des noeuds
	List_Node* list_node;

}Map;

#endif
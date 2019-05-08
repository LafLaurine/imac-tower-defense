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

//Initialisation de la carte
Map* init_map (char* path);
//Vérification de la carte
int map_verification(Map* map, char* map_itd);
//Change couleur en fonction de l'image
int change_path_color(Image* img, unsigned char* pixels, Map* map, float r, float g, float b);
int change_node_color(Image* img, unsigned char* pixels, Map* map, float r, float g, float b);
int change_construct_color(Image* img, unsigned char* pixels, Map* map, float r, float g, float b);
int change_in_color(Image* img, unsigned char* pixels, Map* map, float r, float g, float b);
int change_out_color(Image* img, unsigned char* pixels, Map* map, float r, float g, float b);
int change_map_color(Image* img, unsigned char* pixels, Map* map);
//Check les chemins
int check_segment(int x1, int y1, int x2, int y2, Map* map);
//check les pixels
int check_pixel(int x, int y, Map* map);
//Libere la carte
void free_map(Map* map);

#endif
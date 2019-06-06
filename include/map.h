#ifndef MAP_H
#define MAP_H

#include "colors.h"
#include "image.h"
#include "node.h"

typedef struct Map {
	Image* img; // PPM image
	Color3f path; // Path color
	Color3f node; // Node color
	Color3f construct; // Construct color
	Color3f in; // In area color
	Color3f out; // Out area color
	unsigned int number_node; // Node number
	List_Node* list_node; // Node list
} Map;

// Map initialisation
Map* init_map (char* path);
// Check map
int check_map(Map* map, char* map_itd);
// Change color
Color3f change_color(float r, float g, float b);
// Check X path - Bressenham
int check_segment_X(int x1, int y1, int x2, int y2, Map* map);
// Check Y path - Bressenham
int check_segment_Y(int x1, int y1, int x2, int y2, Map* map);
// Check pixels
int check_pixel(int x, int y, Map* map, Color3f color);
//  Djisksra initialisation
void init_djisksra(Map map, int* tab_chemin);
// Free map
void free_map(Map* map);

#endif
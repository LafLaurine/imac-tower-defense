#ifndef TOWER
#define TOWER

#include <stdio.h>
#include "node.h"
#include "map.h"
#define TOWERRAY 34


typedef enum{
	MEDOC, BANDAGE, GBLANC, GROUGE
}TowerType;


typedef struct Tower {
	float x; // x Position
	float y; // y Position
	TowerType type; // Tower type
	float rate; // Shooting rate
	float power; // Shooting power
	float range; // Shooting range
	int cost; // Tower cost
    //son chemin = noeud A SUPPRIMER ??
    Node* node_prev;
	//Noeud suivant (carte)
	Node* node_next;
	struct Tower* t_prev; // Previous tower
	struct Tower* t_next; // Next tower
} Tower;


// Tower List
typedef struct List_Tower {
	size_t length; // Length list tower
	Tower *t_first; // Pointer to first element
	Tower *t_last; // Pointer to last element
} List_Tower;


// Create new tower list
List_Tower* new_tower_list();
// Create new tower
Tower* create_tower(TowerType type, float x, float y, List_Tower* l_tower, int money);
// Add tower to list
void add_tower_list(Tower* t, List_Tower* l_tower);
// Delete tower from list
void delete_from_position(List_Tower* l_tower, Tower* current);
// Check on which tower we clicked
Tower* click_tower(List_Tower* l_tower, float x, float y);
// Destroy tower
void destroy_tower(List_Tower* l_tower);
// Check if click to create tower is on construct area
int tower_on_construct(Map* map, int x, int y);
// Remove tower
List_Tower* remove_tower(List_Tower* current_m, Tower* current);
// Free all tower from list
void free_all_tower(List_Tower* l_tower);

#endif
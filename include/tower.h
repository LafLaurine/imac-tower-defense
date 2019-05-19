#ifndef TOWER
#define TOWER

#include "node.h"

typedef enum{
	LASER, ROCKET, YELLOW, BLUE
}TowerType;


typedef struct Tower {
	//position
	float x;
	float y;
	//Type de la tour
	TowerType type;
	//cadence 
	int rate;
    //puissance de tir de la tour
	int power;
    //porté de la tour
	int range;
	//cout de la tour
	int cost;
    //son chemin = noeud
    Node* node_prev;
	//Noeud suivant (carte)
	Node* node_next;
	//tour precedente
	struct Tower* t_prev;
	//tour suivante
	struct Tower* t_next;
} Tower;

//liste tour
typedef struct List_Tower {
	//Taille de la liste
	size_t length;
	Tower *t_first; //pointeur vers le premier element
	Tower *t_last; //pointeur vers le dernier element
} List_Tower;

List_Tower* new_tower_list();
Tower* create_tower(TowerType type, float x, float y, Node* head, List_Tower* l_tower);
void add_tower_list(Tower* t, List_Tower* list_tower);
List_Tower* delete_from_position(List_Tower* list_tower, Tower* current);
void destroy_tower(List_Tower* list_tower);
int tower_on_tower(List_Tower* list_tower, float x, float y);
int is_intersect(float x1, float y1, float x2, float y2, float size);

#endif
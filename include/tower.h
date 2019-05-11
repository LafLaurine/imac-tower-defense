#ifndef TOWER
#define TOWER

#include "node.h"

typedef enum{
	LASER, ROCKET, HYBRIDE, MITRAILLETTE
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
Tower* create_tower(Tower* t, TowerType type, float x, float y, int rate, int power, int range, int cost, Node* head);
void add_tower_list(Tower* t, List_Tower* list_tower);
List_Tower* delete_from_position(List_Tower* list_tower, Tower* current);
void destroy_tower(List_Tower* list_tower);

#endif
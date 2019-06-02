#ifndef TOWER
#define TOWER

#include "node.h"
#include "map.h"
#include "common.h"

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
	float rate;
    //puissance de tir de la tour
	float power;
    //porté de la tour
	float range;
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
Tower* create_tower(TowerType type, float x, float y, Node* head, List_Tower* l_tower, int money);
void add_tower_list(Tower* t, List_Tower* list_tower);
List_Tower* delete_from_position(List_Tower* list_tower, Tower* current);
Tower* click_tower(List_Tower* p_ltower, float x, float y);
void destroy_tower(List_Tower* list_tower);
Tower* tower_on_select(Tower* t, List_Tower* l_tower, float x, float y);
int tower_on_construct(Map* map, int posX, int posY);

#endif
#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"
#include "tower.h"

#define WAVESIZE 10;

// enum type monster
typedef enum{BACTERY, VIRUS} Monster_Type;

typedef struct Monster {

	//position du monstre
	float x;
	float y;
	//direction des sprites
	int direction;
    //son chemin = noeud
    Node* node_prev;
	//Noeud suivant (carte)
	Node* node_next;
	//point de vie courant
	int pv;
	//pt vie max
	int pv_max;
	//vitesse deplacement
	int speed;
	//qd il meurt, player gagne ... argent
	int money;
	//type
	Monster_Type type;
	//resistance
	int resist;
	//type tour auquel il resiste
	TowerType type_tower;
	//monstre precedent
	struct Monster* m_prev;
	//monstre suivant
	struct Monster* m_next;
}Monster;


//liste monstre = wave
typedef struct List_Monster {

	//Taille de la liste
	size_t length;
	Monster *m_first; //pointeur vers le premier element
	Monster *m_last; //pointeur vers le dernier element

}List_Monster;


List_Monster* new_monster_list();
Monster* create_monster(List_Monster* list_monster, Monster *m, int pv, int pv_max, int resist, Monster_Type type, TowerType type_t, int speed, int money, Node* head);
void add_monster_list(Monster* m, List_Monster* list_monster);
Monster* level_up(Monster* m, int lvl);
List_Monster* kill_monster(List_Monster* list_monster, Monster* m);
void free_list_monster(List_Monster* list_monster);

#endif
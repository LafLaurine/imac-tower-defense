#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"
#include "tower.h"

#define WAVENUMBER 10

// enum type monster
typedef enum{BACTERY, VIRUS} Monster_Type;

typedef struct Monster {

	//position du monstre
	float x;
	float y;

	//Noeud suivant (carte)
	Node* node_next;
	//point de vie courant
	int pv;
	//pt vie max
	int pv_max;
	//vitesse deplacement
	int move;
	int speed;
	//qd il meurt, player gagne ... argent
	int money;

	//type
	Monster_Type type;
	//resistance
	int resist;
	//monstre suivant
	struct Monster* m_next;
	//monstre precedant
	struct Monster* m_prev;
}Monster;

typedef struct List_Monster {
	Monster* m_first;
	Monster* m_last;
	int nb_monsters; // Nombre monstre dans la liste
	int nb_monsters_send; // Nombre de monstre déjà envoyés
}List_Monster;

//wave
typedef struct Wave {
	List_Monster* lists[WAVENUMBER];
	int nb_lists;
}Wave;


List_Monster* new_monster_list();
Monster* create_monster(Monster_Type type, float x, float y, int pv, int money, int resist, Node *node_next, List_Monster* l_monster);
Monster* add_monster(Monster* m, Monster* new_monster);
void add_monster_list(Monster* m, List_Monster* list_monster);
Monster_Type kill_monster(List_Monster* list_monster, Monster* current);
#endif
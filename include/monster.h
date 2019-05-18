#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"
#include "tower.h"

#define WAVENUMBER 20

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
}Monster;

typedef struct List_Monster {
	Monster* m_first;
	int nb_monsters; // Nombre monstre dans la liste
	int nb_monsters_send; // Nombre de monstre déjà envoyés
}List_Monster;

//wave
typedef struct Wave {
	List_Monster* lists[WAVENUMBER];
	int nb_lists;
}Wave;

// Structure liste stockant les monstres à la portée d'une tour 
/*
typedef struct MonsterToReach {
	int distance;
	Monster* monster;
	int listNum;
	struct MonsterToReach* next;
}MonsterToReach;*/

List_Monster* new_monster_list();
int count_monsters(Monster* m);
Monster* create_monster(Monster_Type type, float x, float y, Node *node_next, int nb_lists);
Monster* add_monster(Monster* m, Monster* new_monster);
Monster* kill_monster(Monster* monsterList, Monster* monster);

#endif
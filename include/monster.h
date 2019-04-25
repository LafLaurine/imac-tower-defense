#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"
#include "tower.h"
#define WAVESIZE 10;


typedef enum{Monster_1, Monster_2} Monster_Type;

typedef struct Monster {

	//position du monstre
	float x;
	float y;
	int direction;
    //son chemin = noeud
    Node* node_prev;
	//Noeud suivant (carte)
	Node* node_next;
	//point de vie
	int pv;
	//vitesse
	int speed;
	//qd il meurt
	int money;
	//type
	Monster_Type type;
	int resist;
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

List_Monster* new_list();
List_Monster* create_monster(Monster* m,TowerType type_t, int pv, int resist, Monster_Type type, int speed, int money, Node* head);
//when monster is touched
void kill_monsters(List_Monster* list_monster);

#endif
#ifndef MONSTER
#define MONSTER

#include "node.h"
#define LIFE 1
#define SPEED 1

typedef enum{Monster_1, Monster_2} Monster_Type;

typedef struct Monster {

	//position du monstre
	float x;
	float y;
	int direction;
    //son chemin = noeud
	//Noeud précédent (carte)
	Node* node_prev;
	//Noeud suivant (carte)
	Node* node_next;
	//type de monstre
	char* type;
	//point de vie
	int pv;
	//vitesse
	int speed;
	//qd il meurt
	int money;
	//type
	Monster_Type type;
}Monster;

//liste monstre
typedef struct List_Monster {

	//Taille de la liste
	size_t length;
	Monster *m_first; //pointeur vers le premier element
	Monster *m_last; //pointeur vers le dernier element

}List_Monster;

#endif
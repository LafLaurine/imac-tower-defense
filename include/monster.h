#ifndef MONSTER_H__
#define MONSTER_H__

#include "node.h"
#define WAVESIZE 10;


typedef enum{Monster_1, Monster_2} Monster_Type;

typedef struct Monster {

	//position du monstre
	float x;
	float y;
	int direction;
    //son chemin = noeud
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

Monster* create_monster(Monster* m, int pv, MonsterResist resist, int speed, int money);
Monster* set_position(Monster* monster, float x, float y);
//when monster is touched
Monster* set_pv(Monster* m, int pv);

#endif
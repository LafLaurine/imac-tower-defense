#include <stdlib.h>
#include <stdio.h>
#include "../include/monster.h"

List_Monster* new_list() {
	List_Monster *list_monster = malloc(sizeof(List_Monster));
	if (list_monster != NULL) {
		list_monster->length = 0;
		list_monster->head = NULL;
		list_monster->tail = NULL;
	}
	else {
		printf("%s\n", "Not enough memory");
		return NULL;
	}

	return list_monster;
}

List_Monster* create_monster(Monster* m,TowerType type_t, int pv, int resist, Monster_Type type, int speed, int money, Node* head){
	List_Monster *list_monster = malloc(sizeof(List_Monster));
	if (m != NULL) {
		m->type = type; //type
		m->pv = pv; //Points de vie
		m->resist = resist; //La résistance
		m->type_tower = type_t; //Le type de tour dont elle est résistante
		m->speed = speed; //La vitesse de déplacement
		m->money = money; //argent gagne
		m->x = head->x; //position x du noeud
		m->y = head->y; //position y du noeud
		m->node_prev = head; //Pointeur vers le premier noeud
		m->node_next = head->next; //Pointeur vers le second noeud
		m->p_next = NULL; 
		if (list_monster->tail == NULL) {
				// Pointe la tête de la liste sur le nouveau monstre
				list_monster->head = m; 
				m->m_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				m->m_prev = list_monster->tail; 
				list_monster->tail->next = m;  
			}
			
			// Pointe la fin de la liste sur le nouveau monstre
			list_monster->tail = m; 

			// On augmente de 1 la taille de la liste
			list_monster->length++; 
		}

	else {
		printf("%s\n", "Fail to create monster");
		return 0;
	}
	return m;
}



void kill_monsters(List_Monster* list_monster) {
	//Si la liste n'est pas vide
	if (list_monster->length != 0) {
		free(list_monster);
	}
}


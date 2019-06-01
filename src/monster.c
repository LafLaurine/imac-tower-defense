#include <stdlib.h>
#include <stdio.h>
#include "../include/monster.h"

List_Monster* new_monster_list() {
	List_Monster *list_monster = malloc(sizeof(List_Monster));
	if (list_monster != NULL) {
		list_monster->m_last = NULL;
		list_monster->m_first = NULL;
		list_monster->nb_monsters = 0;
        list_monster->nb_monsters_send = 0;
	}
	else {
		printf("%s\n", "Not enough memory");
		exit(EXIT_FAILURE);
	}

	return list_monster;
}

Monster* create_monster(Monster_Type type, float x, float y, Node *node_next, List_Monster *l_monster){
    if(node_next == NULL) {
        fprintf(stderr, "pointer is NULL in createMonster function \n");
        exit(1);
    }
    Monster* m = (Monster*)malloc(sizeof(Monster));
    if(m != NULL) {
        if(type == BACTERY) {
            m->pv_max = 100;
            m->pv = 100;
            m->resist = 5;
            m->move = 1;
            m->speed = 1;
            m->money = 5;
        }
        else if(type == VIRUS) {
            m->pv_max = 50;
            m->pv = 50;
            m->resist = 10;
            m->move = 0;
            m->speed = 0;
            m->money = 10;
        }
        //la resistance et l'argent gagné augmente en fonction des vagues
        m->type = type;
        m->x = x;
        m->y = y;
        m->node_next = node_next;
        m->m_next = NULL;
        m->m_prev = NULL;
        add_monster_list(m, l_monster);
    }
    else {
        printf("%s\n", "Not enough memory for monster");
    }
	return m;
}

void add_monster_list(Monster* m, List_Monster* list_monster){
	if (list_monster != NULL) {
		if (list_monster->m_last == NULL) {
				// Pointe la tête de la liste sur le nouveau monstre
				list_monster->m_first = m;
                m->m_prev = NULL;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
                m->m_prev = list_monster->m_last;
				list_monster->m_last->m_next = m; 
			}

            list_monster->m_last = m;

			// On augmente de 1 la taille de la liste
			list_monster->nb_monsters++;
            printf("NB MONSTRES :%d\n", list_monster->nb_monsters); 
		}
	else {
		printf("%s\n", "Fail to add to list tower");
	}
}

void kill_monster(List_Monster *l_monster, Monster* m) {
    if (l_monster != NULL) {
        // If monster to kill is the first of the list
		if (l_monster->m_last == m) {
                l_monster->m_last = m->m_prev;
                free(m);
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
                Monster *mCheck = l_monster->m_last;
                while(mCheck->m_prev != m && mCheck->m_prev != NULL){
                    mCheck = mCheck->m_prev;
                }
                if(mCheck->m_prev == m){
                    mCheck->m_prev = m->m_prev;
                }
			}

			// On diminue de 1 la taille de la liste
			l_monster->nb_monsters--; 
		}
	else {
		printf("%s\n", "Cannot kill monster");
	}
}

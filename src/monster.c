#include <stdlib.h>
#include <stdio.h>
#include "../include/monster.h"

List_Monster* new_monster_list() {
	List_Monster *list_monster = malloc(sizeof(List_Monster));
	if (list_monster != NULL) {
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
            m->pv_max = 20;
            m->pv = 20;
            m->resist = 5;
            m->move = 1;
            m->speed = 1;
            m->money = 5;
        }
        else if(type == VIRUS) {
            m->pv_max = 40;
            m->pv = 40;
            m->resist = 10;
            m->move = 0;
            m->speed = 0;
            m->money = 10;
        }
        //la resistance et l'argent gagné augmente en fonction des vagues
        m->type = type;
        m->x = x;
        printf("LE MONSTRE EN X%f",x);
        m->y = y;
        printf("LE MONSTRE EN Y%f",m->x);
        m->node_next = node_next;
        m->m_next = NULL;

        add_monster_list(m, l_monster);
    }
    else {
        printf("%s\n", "Not enough memory for monster");
    }
	return m;
}

/*
Monster* add_monster(Monster* m, Monster* new_monster){
	if (m != NULL && new_monster!= NULL) {
		// Pointe le monstre suivant de la liste sur le nouveau
		m->m_next = new_monster; 
    }
	else {
		printf("%s\n", "Fail to add to list monster");
        exit(EXIT_FAILURE);
	}
    return new_monster;
}*/

void add_monster_list(Monster* m, List_Monster* list_monster){
	if (list_monster != NULL) {
		if (list_monster->m_first == NULL) {
				// Pointe la tête de la liste sur le nouveau monstre
				list_monster->m_first = m;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				list_monster->m_first->m_next = m; 
			}

			// On augmente de 1 la taille de la liste
			list_monster->nb_monsters++;
            printf("NB MONSTRES :%d\n", list_monster->nb_monsters); 
		}
	else {
		printf("%s\n", "Fail to add to list tower");
	}
}

/*
Monster* kill_monsters(Monster* monsterList, Monster* monster) {
    if(monsterList == NULL) {
        fprintf(stderr, "Cannot kill monster\n");
        exit(1);
    }

    Monster* root = monsterList;
    Monster* rmvMonster;

    // Si le monstre à supprimer est le premier de la liste
    if(monsterList == monster) {
        rmvMonster = monsterList;
        if(monsterList->m_next != NULL) { 
            monsterList = monsterList->m_next;
            free(rmvMonster);
            return monsterList;
        }
        else {
            free(rmvMonster);
            exit(EXIT_FAILURE);
        }
    }
    while(monsterList->m_next != NULL) {
        if(monsterList->m_next == monster) {
            rmvMonster = monsterList->m_next;
            if(rmvMonster->m_next != NULL) {
                monsterList->m_next = rmvMonster->m_next;
            }
            else {
                monsterList->m_next = NULL;
            }
            free(rmvMonster);
        }
        monsterList = monsterList->m_next;
    }
    return root;
}

void kill_one_monster(Monster* m) {
    if(m != NULL) {
        //kill_one_monster(m->m_next);
        free(m);
    }
}
*/

void kill_monster(List_Monster *l_monster, Monster* m) {
    if (l_monster != NULL) {
        // If monster to kill is the first of the list
		if (l_monster->m_first == m) {
                l_monster->m_first = m->m_next;
                free(m);
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
                Monster *mCheck = l_monster->m_first;
                while(mCheck->m_next != m && mCheck->m_next != NULL){
                    mCheck = mCheck->m_next;
                }
                if(mCheck->m_next == m){
                    mCheck->m_next = m->m_next;
                }
			}

			// On diminue de 1 la taille de la liste
			l_monster->nb_monsters--; 
		}
	else {
		printf("%s\n", "Cannot kill monster");
	}
}

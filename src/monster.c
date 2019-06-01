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

void kill_monster(List_Monster* list_monster, Monster* current) {
	if (list_monster != NULL) {

		if(current != NULL) {

			//Si c'est la dernière tour de la liste
			if (current->m_next == NULL) {
				
				//Pointe la fin de la liste sur la tour précédente
				list_monster->m_last = current->m_prev;

				if(list_monster->m_last != NULL) {
					//Lien de la dernière tour vers la tour suivante est NULL
					list_monster->m_last->m_next = NULL;
				}
				else
					list_monster->m_first = NULL;
					
			}
		
			//Si c'est la première de la liste
			else if (current->m_prev == NULL) {
				list_monster->m_first = current->m_next;

				if(list_monster->m_first != NULL) {
			 		list_monster->m_first->m_prev = NULL;
				}
				else
					list_monster->m_last = NULL;
			}

			else {
				//Relie la tour suivante à la tour précédente de la tour que l'on veut supprmer 
				current->m_next->m_prev = current->m_prev;
				//Relie la tour précédente à la tour suivante de la tour que l'on veut supprmer 
				current->m_prev->m_next = current->m_next;

			}
			//supprime la tour
			free(current);
			list_monster->nb_monsters--;
            printf("NB MONSTRES :%d\n", list_monster->nb_monsters); 
		}
		else {
			fprintf(stderr, "Tower doesn't exist");
			exit(EXIT_FAILURE);
		}
	}
	else {
		fprintf(stderr, "Tower list doesn't exist");
		exit(EXIT_FAILURE);
	} 
}
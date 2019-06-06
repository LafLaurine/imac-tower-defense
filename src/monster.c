#include "../include/monster.h"

List_Monster* new_monster_list() {
	List_Monster *l_monster = malloc(sizeof(List_Monster));

	if (l_monster != NULL) {
		l_monster->m_last = NULL;
		l_monster->m_first = NULL;
		l_monster->nb_monsters = 0;
        l_monster->nb_monsters_send = 0;
	} else {
		printf("Not enough memory\n");
		exit(EXIT_FAILURE);
	}

	return l_monster;
}

Monster* create_monster(Monster_Type type, float x, float y, Node *node_next, List_Monster* l_monster){
    if(node_next == NULL) {
        printf("pointer is NULL in createMonster function \n");
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
        m->type = type;
        m->x = x;
        m->y = y;
        m->node_next = node_next;
        m->m_next = NULL;
        m->m_prev = NULL;
        add_monster_list(m, l_monster);

    } else {
        printf("Not enough memory for monster\n");
    }

	return m;
}

void add_monster_list(Monster* m, List_Monster* l_monster){
	if (l_monster != NULL) {
		if (l_monster->m_last == NULL) {
				// List last on new monster
				l_monster->m_first = m;
                m->m_prev = NULL;
			}
			// If elements are already into list
			else {
                m->m_prev = l_monster->m_last;
				l_monster->m_last->m_next = m; 
			}

			// List last on new monster
            l_monster->m_last = m;
			// Nb monster +1
			l_monster->nb_monsters++;
		} else {
			printf("Fail to add to list monster\n");
	}
}

Monster_Type kill_monster(List_Monster* l_monster, Monster* current) {
	if (l_monster != NULL) {
		if(current != NULL) {
			Monster_Type type = current->type;

			// If last monster of list
			if (current->m_next == NULL) {
				
				// End of list on previous monster
				l_monster->m_last = current->m_prev;

				if(l_monster->m_last != NULL) {
					// Last monster next is NULL
					l_monster->m_last->m_next = NULL;
				}
				else
					l_monster->m_first = NULL;
					
			}
		
			// Last monster next is NULL
			else if (current->m_prev == NULL) {
				l_monster->m_first = current->m_next;

				if(l_monster->m_first != NULL) {
			 		l_monster->m_first->m_prev = NULL;
				}
				else
					l_monster->m_last = NULL;
			} else {
				// Link next monster to previous monster (soon deleted) 
				current->m_next->m_prev = current->m_prev;
				// Link previous monster to next monster (soon deleted)
				current->m_prev->m_next = current->m_next;
			}

			// Delete monster
			free(current);
			l_monster->nb_monsters--;
			return type;
		}
		else {
			fprintf(stderr, "Monster doesn't exist");
			return -1;
		}
	} else {
		fprintf(stderr, "Monster list doesn't exist");
		return -1;
	}
}

List_Monster* remove_monster(List_Monster* current_m, Monster* current) {
	// Check if list allocated
	if (current_m != NULL) {
		if(current != NULL) {
			// List head on next node
			current_m->m_first = current->m_next;
			free(current);
			current_m->nb_monsters--;

		} 
	} else 
		printf("Couldn't find list\n");

	// Return new list
	return current_m; 
}

void free_all_monster(List_Monster* l_monster) {
	// If list not empty
	if (l_monster->nb_monsters != 0) {
		//	While list not NULL
		Monster* temp = l_monster->m_last;
		while(temp != NULL) {
			if(temp->m_prev != NULL){
				l_monster = remove_monster(l_monster, temp->m_next);
				temp = temp->m_prev;
			} else {
				l_monster = remove_monster(l_monster, temp);
				temp = NULL;
			}
		}
	}
	free(l_monster);
}
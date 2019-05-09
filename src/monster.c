#include <stdlib.h>
#include <stdio.h>
#include "../include/monster.h"
#include "../include/tower.h"

List_Monster* new_monster_list() {
	List_Monster *list_monster = malloc(sizeof(List_Monster));
	if (list_monster != NULL) {
		list_monster->length = 0;
		list_monster->m_first = NULL;
		list_monster->m_last = NULL;
	}
	else {
		printf("%s\n", "Not enough memory");
		return NULL;
	}

	return list_monster;
}

Monster* create_monster(List_Monster* list_monster, Monster* m, int pv, int pv_max, int resist, Monster_Type type, TowerType type_t, int speed, int money, Node* head){
    if (list_monster != NULL) {
        if(m != NULL) {
            m->type = type; //type
            m->pv = pv_max; //Points de vie (au début c'est au max)
            m->pv_max = pv_max; //Points de vie
            m->resist = resist; //La résistance
            m->type_tower = type_t; //Le type de tour dont elle est résistante
            m->speed = speed; //La vitesse de déplacement
            m->money = money; //argent gagne
            m->x = head->x; //position x du noeud
            m->y = head->y; //position y du noeud
            m->node_prev = head; //Pointeur vers le premier noeud
            m->node_next = head->next; //Pointeur vers le second noeud
            add_monster_list(m,list_monster);
        } else {
            fprintf(stderr, "Cannot create new monster\n");
            exit(EXIT_FAILURE);
        }
    } else {
            fprintf(stderr, "Cannot add monster \n");
            exit(EXIT_FAILURE);
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
			
			// Pointe la fin de la liste sur le nouveau monstre
			list_monster->m_last = m; 

			// On augmente de 1 la taille de la liste
			list_monster->length++; 
		}
	else {
		printf("%s\n", "Fail to add to list monster");
	}
}

Monster* level_up(Monster* m, int lvl) {

    if(m != NULL) {
        m->pv += lvl * 10;
        m->resist += lvl * 10;
        m->money += lvl * 2;
    }
    else {
        fprintf(stderr, "Monster doesn't exist\n");
        return 0;
    }
    return m;
}

List_Monster* kill_monster(List_Monster* list_monster, Monster* m) {

    // On vérifie si notre liste a été allouée
    if (list_monster != NULL) {
        if(m != NULL) {
            //Si c'est le dernier monstre de la liste
            if (m->m_next == NULL) {
                printf("%s\n", "lalala");

                list_monster->m_last = m->m_prev;
                if(list_monster->m_last != NULL) {
                    //Lien du dernier monstre vers le monstre suivant est NULL
                    list_monster->m_last->m_next = NULL;
                }
                else
                    list_monster->m_first = NULL;
                
            }
            //Si c'est le premier monstre de la liste
            else if (m->m_prev == NULL) {
                list_monster->m_first = m->m_next;

                if(list_monster->m_first != NULL) {
                    list_monster->m_first->m_prev = NULL;
                }
                else
                    list_monster->m_last = NULL;
            }

            else {
                //Relie le monstre suivant au monstre précédent du monstre que l'on veut supprimer 
                m->m_next->m_prev = m->m_prev;
                //Relie le monstre précédent au monstre suivant du monstre que l'on veut supprimer 
                m->m_prev->m_next = m->m_next;
            }
            free(m);
            list_monster->length--;

        }
        else {
            fprintf(stderr, "Find no monster\n");
            return NULL;
        }
    }
    else {
        fprintf(stderr, "Monster list desn't exist\n");
        return NULL;
    }

    // on retourne notre nouvelle liste
    return list_monster; 
}

void free_list_monster(List_Monster* list_monster) {
	//Si la liste n'est pas vide
	if (list_monster->length != 0) {
        while (list_monster->m_first != NULL) {
            //list_monster = kill_monster(list_monster, list_monster->m_first);

        }
	}
    free(list_monster);
}

//IL FAUT ADAPTER DIJKSTRA 

/*
void initialisation_dijkstra(int ** distance, int sommet, int nb_sommet)
{
    int i;
    for(i = 0; i < nb_sommet; i++)
    {
        distance[i][PARCOURU] = false;
        distance[i][POIDS] = -1;
        distance[i][ANTECEDENT] = -1;
        nombre_operation += 4;
    }
    distance[sommet][POIDS] = 0;// On initialise le sommet de départ à 0.
    nombre_operation++;
}

void dijkstra(matrice_adjacente * m,int ** distance, int sommet)
{
    int i, j;
    nombre_operation++;
    initialisation_dijkstra(distance, sommet, m->nombre_sommet);
    for(i = 0; i < m->nombre_sommet; i++)  // pour cq sommet i
    {
        int poids_actu = -1, sommet_actu = -1;
        nombre_operation+= 2;
        for(j = 0; j < m->nombre_sommet; j++) // pour cq sommet j
        {
            if(!distance[j][PARCOURU] && distance[j][POIDS] > -1 && (distance[j][POIDS] < poids_actu || sommet_actu == -1))
            {
                //Si le sommet j n'a pas été parcouru, que son poids est sup à 0 et que le poids du sommet j est inférieur ou que le sommet actuel
                 //est égal à -1, donc aucun sommet marqué. On marque ainsi le sommet non parcouru, ayant le plus petit poids positif 
                sommet_actu = j;
                poids_actu = distance[j][POIDS];
                nombre_operation+=2;
            }
            nombre_operation+=4;
        }
        nombre_operation++;
        if(sommet_actu != -1)
        {
            for(j = 0; j < m->nombre_sommet; j++)
            {
                nombre_operation++;
                if(m->matrice[sommet_actu][j][CHEMIN] == 1)  // sommet = -1
                {
                    // on met à jours chaque poids
                    update(distance[sommet_actu][POIDS], m->matrice[sommet_actu][j][POIDS], sommet, j, distance);
                    nombre_operation++;
                }
            }
            distance[sommet_actu][PARCOURU] = true;
            nombre_operation++;
        }
    }
    for(i = 0 ; i < m->nombre_sommet; i++)
        afficherCheminPlusCourt(distance, sommet, i);
}

void update(int poidsPere, int poidsfils, int sommet_pere, int sommet_fils, int **etat_dji)
{
    nombre_operation+=3;
    if(!etat_dji[sommet_fils][PARCOURU] && (etat_dji[sommet_fils][POIDS] <= 0 || poidsfils + poidsPere < etat_dji[sommet_fils][POIDS]))
    {
        etat_dji[sommet_fils][POIDS] = poidsfils + poidsPere;
        etat_dji[sommet_fils][ANTECEDENT] = sommet_pere;
        nombre_operation+=2;
    }
    return;
}


void afficherCheminPlusCourt(int **etat_final, int sommet_depart, int sommet_final)
{
    if(sommet_depart == sommet_final)
        return;
    printf("Les plus courts chemins à partir de %d ont les valeurs suivantes", sommet_final);
    int current = sommet_final;
    int poids = 0;
    while(current != sommet_depart)
    {
        if(current == -1)
            return;
        poids += etat_final[current][POIDS];
        current = etat_final[current][ANTECEDENT];
    }
    printf("\nde %d au sommet %d : %d.\n", sommet_depart, sommet_final, poids);
}

void plusCourtChemin(matrice_adjacente *m, int sommet, char nom[50])
{
    int i,j;
    nombre_operation = 1;
    int **distance = malloc(sizeof(int*) * m->nombre_sommet);
    for(i = 0; i < m->nombre_sommet; i++)
    {
        distance[i] = malloc(sizeof(int) * 3);
    }
    dijkstra(m, distance, sommet);
    for(i = 0; i < m->nombre_sommet; i++)
    {
        free(distance[i]);
    }
    free(distance);
}*/
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

int count_monsters(Monster* m) {
    int cpt = 1;
    while(m->m_next != NULL) {
        cpt++;
        m = m->m_next;
    }
    return cpt;
}

Monster* create_monster(Monster_Type type, float x, float y, Node *node_next, int nb_lists){
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
        //la resistance augmente en fonction des vagues
        m->resist += 10*nb_lists;
        m->money += 5*nb_lists;
        m->type = type;
        m->x = x;
        m->y = y;
        m->node_next = node_next;
        m->m_next = NULL;
    }

    else {
        printf("%s\n", "Not enough memory for monster");
    }
	return m;
}


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
}

Monster* kill_monster(Monster* monsterList, Monster* monster) {
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
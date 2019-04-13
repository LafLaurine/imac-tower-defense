#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "../include/graphe.h"
#include "../include/node.h"
int nombre_operation;

List_Node* new_List_Node() {
    
    //Alloue de la mémoire 
    List_Node* lnode = malloc(sizeof(List_Node));
    if (lnode != NULL) {
        lnode->length = 0;
        lnode->head = NULL;
        lnode->tail = NULL;
    }
    return lnode;
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
                /*Si le sommet j n'a pas été parcouru, que son poids est sup à 0 et que le poids du sommet j est inférieur ou que le sommet actuel
                 est égal à -1, donc aucun sommet marqué. On marque ainsi le sommet non parcouru, ayant le plus petit poids positif */
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
#ifndef GRAPHE_H
#define GRAPHE_H

#define PARCOURU 0
#define POIDS 1
#define ANTECEDENT 2
#define NEW_POIDS 3
#define ORDRE 0
#define DEGRE_ENTRANT 1
#define PARCOURU 0
#define ANTECEDENT 2
#define NEW_POIDS 3
#define ORDRE 0
#define CHEMIN 0
#define POIDS 1


typedef struct arc
{
    int head;
    int queue;
    int poids;

} arc;

typedef struct graphe_chargement
{
    int nombre_arc;
    int nombre_sommet;
    arc *arc_graphe;
} graphe_chargement;


typedef struct matrice_adjacente
{
    int ***matrice;
    int nombre_sommet;
} matrice_adjacente;

void plusCourtChemin(matrice_adjacente *m, int sommet);
void initialisation_dijkstra(int ** distance, int sommet, int nb_sommet);
void dijkstra(matrice_adjacente * m,int ** distance, int sommet);
void update(int poidsPere, int poidsfils, int sommet_pere, int sommet_fils, int **etat_dji);
void afficherCheminPlusCourt(int **etat_final, int sommet_depart, int sommet_final);
void chargementGraphe(graphe_chargement *g, char * nom_fichier);

#endif

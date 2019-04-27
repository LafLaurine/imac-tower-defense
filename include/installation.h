#ifndef INSTALLATION
#define INSTALLATION

#include "node.h"
#include "tower.h"

typedef enum{
	radar, usine, stock
} InstallationType;


typedef struct Installation {
	//position
	float x;
	float y;
	//Type de l'installation'
	InstallationType type;
    //son chemin = noeud
    Node* node_prev;
	//Noeud suivant (carte)
	Node* node_next;
	//installation precedente
	struct Installation* t_prev;
	//installation suivante
	struct Installation* t_next;
    //liste tours
    List_Tower* list_tower;
} Installation;

//liste tour
typedef struct List_Installation {
	//Taille de la liste
	size_t length;
	Installation *t_first; //pointeur vers le premier element
	Installation *t_last; //pointeur vers le dernier element

} List_Installation;

List_Installation* new_installation_list();
Installation* create_installation(Installation* t, InstallationType type, float x, float y, Node* head);
void add_installation_list(Installation* t, List_Installation* list_installation);
void destroy_installation(List_Installation* list_installation);
// fonction pour donner bonus aux tours les plus proches

#endif
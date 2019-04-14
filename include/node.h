#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	//Coordonée x du noeud
	float x;
	//Coordonnée y du noeud
	float y;
	//Noeud suivant
	struct Node *next;
}Node;

/* STRUCTURE DE LA LISTE DE NOEUDS */
typedef struct List_Node {
	//Taille de la liste
	size_t length;
	Node *head; //pointeur vers le premier element
	Node *tail; //pointeur vers le dernier element
}List_Node;

//Initialisation de la liste de noeuds
List_Node* new_List_Node();
//Ajouter un noeud à la liste de noeuds
int add_node(List_Node*, float x, float y);
//Supprimer un noeud
List_Node* remove_node(List_Node* current_node, Node* current);
//Supprimer la liste de noeuds
void free_all_node (List_Node* list_node);

#endif
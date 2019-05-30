#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/node.h"


/* Nvlle liste noeud */
List_Node* new_List_Node() {
	List_Node* new_lnode = malloc(sizeof(List_Node));
	if (new_lnode != NULL) {
		new_lnode->length = 0;
		new_lnode->head = NULL;
		new_lnode->tail = NULL;
	}
	return new_lnode;
}

/* Nv noeud dans liste */
/*
int add_node(List_Node* list_node, Node_Type type, float x, float y, int *successors) {

	// On vérifie si notre liste a été allouée
	if (list_node != NULL) {
		//Création d'un nouveau noeud
		Node* new_node = malloc(sizeof(Node));
		int *successors = malloc(sizeof(int*));

		// On vérifie si le malloc n'a pas échoué
		if (new_node != NULL) {
			
			new_node->type = type;
			new_node->x = x; 
			new_node->y = y; 
			printf("New node y position %f\n", new_node->y);
			new_node->successors = successors;
			// Rajoute à la fin : dernier élement de la liste 
			new_node->next = NULL; 

			add_node_list(new_node, list_node);

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (list_node->head == NULL) {
				list_node->head = new_node; // Pointe la tête de la liste sur le nouveau noeud
			} else { // Cas où des éléments sont déjà présents dans la  liste
				new_node->next = list_node->head;
				list_node->head = new_node;  // Relie le dernier de la liste au nouveau noeud
			}

			// Pointe la fin de la liste sur le nouveau noeud
			

			// On augmente de 1 la taille de la liste
			list_node->length++; 
		}
		else {
			printf("Not enough memory\n");
			return 0;
		}
	}
	else {
		printf("Node list doesn't exist\n");
		return 0;
	}

	printf("Node added\n");
	return 1; 
}*/

int create_node(Node_Type type, float x, float y, int *successors, List_Node* l_node){
	Node* n = malloc(sizeof(Node));
	//int *n_successors = malloc(sizeof(int*));

	if(n != NULL) {
		n->type = type; //type
		n->x = x; //coordonnee x
		n->y = y; //coordonnee y
		n->successors = successors;
		n->next = NULL;
		printf("New node y position %f\n", n->y);

		add_node_list(n, l_node);
		return 1;
	} else {
		printf("%s\n", "Not enough memory for node");
		return 0;
	}
}

void add_node_list(Node* n, List_Node* list_node){
	if (list_node != NULL) {
		if (list_node->tail == NULL) { 
				// Pointe la tête de la liste sur le nouveau monstre
				list_node->head = n;
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				n->prev = list_node->tail; 
				list_node->tail->next = n;
			}
			
			// Pointe la fin de la liste sur le nouveau monstre
			list_node->tail = n;

			// On augmente de 1 la taille de la liste
			list_node->length++; 
		}
	else {
		printf("%s\n", "Fail to add to list node");
	}
}


List_Node* remove_node(List_Node* current_node, Node* current) {

	// On vérifie si notre liste a été allouée
	if (current_node != NULL) {

		if(current != NULL) {

			//Pointe la tête de la liste vers le noeud suivante
			current_node->head = current->next;
/*
			if(current_node->head == NULL) 
				current_node->tail = NULL;
			*/
			free(current);
			//Décrémente de un la taille de la liste
			current_node->length--;

		}
		else
			printf("%s\n","node doesn't existrs");
	}
	else 
		printf("%s\n","couldn't find list");

	// on retourne notre nouvelle liste
	return current_node; 
}

void free_all_node(List_Node* list_node) {
	//Si la liste n'est pas vide
	if (list_node->length != 0) {

		//Tant que la liste n'est pas vide
		while (list_node->head != NULL) {
			list_node = remove_node(list_node, list_node->head);
		}
		
	}
	free(list_node);
}

List_Node* free_node_by_position(List_Node* list_node, Node* current) {
	if (list_node != NULL) {

		if(current != NULL) {

			//Pointe la tête de la liste vers le noeud suivante
			list_node->head = current->next;
/*
			if(list_node->head == NULL) 
				list_node->tail = NULL;
			*/
			//Libère espace mémoire : supprime la tour
			free(current);
			//Décrémente de un la taille de la liste
			list_node->length--;

		}
		else
			fprintf(stderr, "Ce noeud n'existe pas");
	}
	else 
		fprintf(stderr, "Cette liste de noeuds n'existe pas");
	return list_node; 
}

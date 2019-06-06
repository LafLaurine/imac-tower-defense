#ifndef NODE_H
#define NODE_H
#define NB_MIN_NOEUDS 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"


typedef enum {
	Test, In, Out, Twist, Intersect
} Node_Type;

typedef struct Node {
	float x; // x Position
	float y; // y Position
	Node_Type type; // Node type
	int* successors; // Node successors
	int nb_successors; // Node successors
	int indice;
	struct Node *next; // Next node
	struct Node *prev; // Previous node
} Node;

// Node list struct
typedef struct List_Node {
	size_t length; // list length
	Node *head; // Pointer to first element
	Node *tail; // Pointer to last element
} List_Node;


// Create new list node
List_Node* new_List_Node();
// Create new node
Node* create_node(Node_Type type, float x, float y, int *successors, int nb_successors, List_Node* l_node, int indice);
// Add node to list
void add_node_list(Node* n, List_Node* list_node);
// Delete one node
List_Node* remove_node(List_Node* current_node, Node* current);
// Delete list of node
void free_all_node (List_Node* list_node);
// Remove node by position
List_Node* free_node_by_position(List_Node* list_node, Node* current);

#endif
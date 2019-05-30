#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#define NB_MIN_NOEUDS 2

typedef enum{In, Out, Twist, Intersect} Node_Type;

typedef struct Node {
	//x node coordonate
	float x;
	//y node coordonate
	float y;
	//Node type
	Node_Type type;
	//Node successors
	int *successors;
	//Next node
	struct Node *next;
	//Next node
	struct Node *prev;
}Node;

//List of node struct
typedef struct List_Node {
	//lenght of list
	size_t length;
	Node *head; //pointeur to first element
	Node *tail; //pointeur to last element
}List_Node;

//Init node's list
List_Node* new_List_Node();
//Create node
int create_node(Node_Type type, float x, float y, int *successors, List_Node* l_node);
//int add_node(List_Node*, Node_Type type, float x, float y, int *successors);
//Add node to list
void add_node_list(Node* n, List_Node* list_node);
//Delete one node
List_Node* remove_node(List_Node* current_node, Node* current);
//Delete list of node
void free_all_node (List_Node* list_node);
//Remove node by position
List_Node* free_node_by_position(List_Node* list_node, Node* current);

#endif
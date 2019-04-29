#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>
#define NB_MIN_NOEUDS 2

typedef enum{In, Out, Twist, Intersect} Node_Type;

typedef struct Node {
	//x node coordonate
	float x;
	//y node coordonate
	float y;
	//Node type
	Node_Type type;
	//Next node
	struct Node *next;
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
//Add node to list
int add_node(List_Node*, float x, float y);
//Delete one node
List_Node* remove_node(List_Node* current_node, Node* current);
//Delete list of node
void free_all_node (List_Node* list_node);
//Remove node by position
List_Node* free_node_by_position(List_Node* list_node, Node* current);

#endif
#include "../include/node.h"

List_Node* new_List_Node() {
	List_Node* new_lnode = malloc(sizeof(List_Node));
	if (new_lnode != NULL) {
		new_lnode->length = 0;
		new_lnode->head = NULL;
		new_lnode->tail = NULL;
	}
	return new_lnode;
}

Node* create_node(Node_Type type, float x, float y, int *successors, List_Node* l_node, int indice){
	Node* n = malloc(sizeof(Node));

	if(n != NULL) {
		n->type = type; //type
		n->x = x; //coordonnee x
		n->y = y; //coordonnee y
		n->successors = successors;
		n->indice = indice;
		n->next = NULL;
		printf("New node y position %f\n", n->y);
		add_node_list(n, l_node);
		return n;

	} else {
		printf("%s\n", "Not enough memory for node");
		return NULL;
	}
}

void add_node_list(Node* n, List_Node* list_node){
	if (list_node != NULL) {
		if (list_node->tail == NULL) { 
				// List head on new node
				list_node->head = n;
			}
			// If elements are already into list
			else {
				n->prev = list_node->tail; 
				list_node->tail->next = n;
			}
			
			// List last on new node
			list_node->tail = n;
			list_node->length++;

		} else {
			printf("Fail to add to list node\n");
	}
}

List_Node* remove_node(List_Node* current_node, Node* current) {
	// Check if list allocated
	if (current_node != NULL) {
		if(current != NULL) {
			// List head on next node
			current_node->head = current->next;
			free(current);
			current_node->length--;

		} else
			printf("Inexistant node\n");
	} else 
		printf("Couldn't find list\n");

	// Return new list
	return current_node; 
}

void free_all_node(List_Node* list_node) {
	// If list not empty
	if (list_node->length != 0) {
		//	While list not NULL
		Node* temp = list_node->tail;
		while(temp != NULL) {
			if(temp->prev != NULL){
				list_node = remove_node(list_node, temp->next);
				temp = temp->prev;
			} else {
				list_node = remove_node(list_node, temp);
				temp = NULL;
			}
		}
	}
	free(list_node);
}

List_Node* free_node_by_position(List_Node* list_node, Node* current) {
	if (list_node != NULL) {
		if(current != NULL) {
			// List head on new node
			list_node->head = current->next;
			// Free memory : delete node
			free(current);
			list_node->length--;
		}
		else
			printf("Inexistant node\n");
	}
	else 
		printf("Inexistant node list\n");
	
	return list_node; 
}

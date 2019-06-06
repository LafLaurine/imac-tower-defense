#ifndef INSTALLATION
#define INSTALLATION

#include <stdio.h>
#include "map.h"


typedef enum{
	RADAR, USINE, STOCK
} InstallationType;


typedef struct Installation {
	float x; // x Position
	float y; // y Position
	InstallationType type; // Installation type
	struct Installation* i_prev; // Previous installation
	struct Installation* i_next; // Next installation
	int cost; // Installation cost
} Installation;


// Installation list
typedef struct List_Installation {
	size_t length; // List length
	Installation *i_first; // Pointer to first element
	Installation *i_last; // Pointer to last element
} List_Installation;


// Create new list installation
List_Installation* new_installation_list();
// Create new installation
Installation* create_installation(InstallationType type, float x, float y, List_Installation* l_inst, int money);
// Check on which installation we clicked
Installation* click_installation(List_Installation* l_inst, float x, float y);
// Delete installation from list
void delete_install_from_position(List_Installation* l_inst, Installation* current);
// Add installation to list
void add_installation_list(Installation* i, List_Installation* l_inst);
// Destroy installation
void destroy_installation(List_Installation* l_inst);
// Check if click to create installation is on construct area
int installation_on_construct(Map* map, int x, int y);
// Remove installation
List_Installation* remove_installation(List_Installation* current_i, Installation* current);
// Free all installation from list
void free_all_inst(List_Installation* l_inst);

#endif
#ifndef INSTALLATION
#define INSTALLATION

#include "node.h"
#include "map.h"
#include "common.h"


typedef enum{
	RADAR, USINE, STOCK
} InstallationType;


typedef struct Installation {
	//position
	float x;
	float y;
	//Type de l'installation'
	InstallationType type;
    //liste tours
    //List_Tower* list_tower;
	//tour precedente
	struct Installation* i_prev;
	//tour suivante
	struct Installation* i_next;
	int cost;
} Installation;

//liste tour
typedef struct List_Installation {
	//Taille de la liste
	size_t length;
	Installation *i_first; //pointeur vers le premier element
	Installation *i_last; //pointeur vers le dernier element

} List_Installation;

List_Installation* new_installation_list();
int create_installation(InstallationType type, float x, float y, List_Installation* list_inst);
Installation* installation_on_select(Installation* i, List_Installation* l_inst, float x, float y);
Installation* click_installation(List_Installation* l_install, float x, float y);
List_Installation* delete_install_from_position(List_Installation* l_inst, Installation* current);
void add_installation_list(Installation* t, List_Installation* list_installation);
void destroy_installation(List_Installation* list_installation);
int installation_on_construct(Map* map, int x, int y);
// fonction pour donner bonus aux tours les plus proches

#endif
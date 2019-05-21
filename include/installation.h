#ifndef INSTALLATION
#define INSTALLATION

#include "node.h"
#include "tower.h"
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
    List_Tower* list_tower;
	//tour precedente
	struct Installation* i_prev;
	//tour suivante
	struct Installation* i_next;
} Installation;

//liste tour
typedef struct List_Installation {
	//Taille de la liste
	size_t length;
	Installation *i_first; //pointeur vers le premier element
	Installation *i_last; //pointeur vers le dernier element

} List_Installation;

List_Installation* new_installation_list();
Installation* create_installation(InstallationType type, float x, float y, List_Installation* list_inst, List_Tower* list_tower);
void add_installation_list(Installation* t, List_Installation* list_installation);
void destroy_installation(List_Installation* list_installation);
int inst_on_inst(List_Installation* list_inst, float x, float y);
int installation_on_construct(Map* map, int x, int y);
// fonction pour donner bonus aux tours les plus proches

#endif
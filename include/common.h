#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
#include <string.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SDL/SDL_mixer.h>
#include "tower.h"
#include "game.h"
#include "installation.h"

// Check if ray1 intersects ray2
int is_intersect(float x1, float y1, float x2, float y2, float r1, float r2);
void vBitmapOutput(int x, int y, char *string, void *font);
// Check if hover tower
Tower* constructTowerSelected(List_Tower* l_tower, int x, int y);
// Check if hover installation
Installation* select_installation_construted(List_Installation* l_inst, int x, int y);
// Check if tower is on building to see if construction is possible
int tower_on_building(List_Tower* list_tower, float x, float y, List_Installation* list_inst);
// Check if installation is on building to see if construction is possible
int inst_on_building(List_Installation* list_inst, float x, float y, List_Tower* list_tower);
// Check around towers if installations
int check_around_tower(Tower* t, List_Installation* list_inst);
// Update tower
void update_tower(Tower* t, InstallationType);
// Check around installation if towers
int check_around_inst(Installation* i, List_Tower* list_tower);
// Delete power upgrade of tower around installatio 
int delete_around_inst(Installation* i, List_Tower* list_tower);
// Click to delete tower
int click_delete_tower(List_Tower* l_tower, Tower* current, Game* game);
// Click to delete installation
int click_installation_delete(List_Installation* l_inst, Installation* current, Game* game, List_Tower* l_tower);
// Shot monsters
int shot_monster(Monster* m, Tower* t);
// Check if monster intersects with range tower
Monster_Type monster_on_tower(List_Monster* list_monster, List_Tower* list_tower);
// Downgrade tower
void downgrade_tower(Tower* t, InstallationType type_inst);

#endif
#ifndef COMMON_H
#define COMMON_H

#include "installation.h"
#include "tower.h"
#include "game.h"

int is_intersect(float x1, float y1, float x2, float y2, float radius);
int square_intersect_circle(float x1, float x2, float y1, float y2, int size_1, int size_2);
int check_around_tower(Tower* t, List_Installation* list_inst);
void update_tower(Tower* t, InstallationType);
int check_around_inst(Installation* i, List_Tower* list_tower);
int click_delete_tower(List_Tower* l_tower, Tower* current, Game* game, float x, float y);

#endif

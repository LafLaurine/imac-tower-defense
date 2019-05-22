#ifndef COMMON_H
#define COMMON_H

#include "installation.h"
#include "tower.h"

int is_intersect(float x1, float y1, float x2, float y2, float radius);
int check_tower(Tower* t, List_Installation* list_inst);

#endif

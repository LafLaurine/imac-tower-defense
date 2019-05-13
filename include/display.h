#ifndef DISPLAY_H
#define DISPLAY_H
#include "sprite.h"
#include "colors.h"
#include "monster.h"

int display_map(GLuint* texture);
void draw_perim(float rayon);
int display_path(Map* map);
int display_monster(GLuint* monster, List_Monster* list_monster);
int display_help(GLuint* texture);
int display_tower(GLuint* tower, List_Tower* list_tower, List_Monster* list_monster, Tower* current);

#endif

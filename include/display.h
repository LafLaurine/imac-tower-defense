#ifndef DISPLAY_H
#define DISPLAY_H
#include "sprite.h"
#include "monster.h"

int display_map(GLuint* texture);
void draw_perim(float rayon);
int display_path(Map* map);
int display_monster(GLuint* monster, List_Monster* list_monster);
int display_help(GLuint* texture);

#endif

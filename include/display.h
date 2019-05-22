#ifndef DISPLAY_H
#define DISPLAY_H
#include "sprite.h"
#include "colors.h"
#include "monster.h"
#include "tower.h"
#include "installation.h"
#define PI 3.14

int display_map(GLuint* texture);
void draw_perim(float rayon);
int display_path(Map* map);
int display_help(GLuint* texture);
int display_monster(Monster* m, SDL_Surface* img, GLuint texture);
int display_wave(Wave wave);
int display_tower(Tower* current, SDL_Surface* tourImg, GLuint *tourTexture);
int display_list_tower(List_Tower* list_tower);
int display_installation(Installation* i, SDL_Surface* instImg, GLuint *instTexture);
int display_list_installation(List_Installation* list_inst);
void drawCircle (int fill, int nbSeg);
int is_intersect(float x1, float y1, float x2, float y2, float radius);
int tower_on_building(List_Tower* list_tower, float x, float y, List_Installation* list_inst);
int inst_on_building(List_Installation* list_inst, float x, float y, List_Tower* list_tower);

#endif

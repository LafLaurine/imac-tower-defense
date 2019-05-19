#ifndef DISPLAY_H
#define DISPLAY_H
#include "sprite.h"
#include "colors.h"
#include "monster.h"
#include "tower.h"
#define PI 3.14

int display_map(GLuint* texture);
void draw_perim(float rayon);
int display_path(Map* map);
int display_help(GLuint* texture);
int display_monster(Monster* m, SDL_Surface* img, GLuint texture);
int display_wave(Wave wave);
int display_tower(Tower* current, SDL_Surface* tourImg, GLuint *tourTexture);
int display_list_tower(List_Tower* list_tower);
void drawCircle (int fill, int nbSeg);

#endif

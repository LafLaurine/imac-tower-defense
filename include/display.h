#ifndef DISPLAY_H
#define DISPLAY_H
#include "sprite.h"
#include "colors.h"
#include "monster.h"

int display_map(GLuint* texture);
void draw_perim(float rayon);
int display_path(Map* map);
int display_help(GLuint* texture);
int display_monster(Monster* m, SDL_Surface* img, GLuint texture);
int display_wave(Wave wave);


#endif

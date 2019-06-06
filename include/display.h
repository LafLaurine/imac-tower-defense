#ifndef DISPLAY_H
#define DISPLAY_H

#include "sprite.h"
#include "monster.h"
#include "tower.h"
#include "game.h"
#include "common.h"
#include "installation.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14

int display_map(GLuint* texture);
// Display right column
void display_right_column();
int display_path(Map* map);
// Display money
int display_money(GLuint* texture);
// Display full
int display_full(GLuint* texture);
// Display monster
int display_monster(Monster* m, SDL_Surface* img, GLuint texture);
// Display all monster of wave
int display_wave(List_Monster *l_monster);
// Display tower
int display_tower(Tower* current, SDL_Surface* tourImg, GLuint *tourTexture);
// Display all tower of list tower
int display_list_tower(List_Tower* list_tower);
// Display range tower
int display_range_tower(Tower* t);
// Display installation
int display_installation(Installation* i, SDL_Surface* instImg, GLuint *instTexture);
// Display all installation of list installation
int display_list_installation(List_Installation* list_inst);
// Display cross
int display_cross(GLuint* texture);
// Display tower features
void displayTowerFeatures(Tower* t);
// Display installation features
void displayInstallationFeatures(Installation* i);
// Display right column down
int display_right_column_down(GLuint *texture);
// Draw circle
void drawCircle (int fill, int nbSeg);
// Draw action perimeter as a circle
void draw_perim(float rayon);


#endif

#ifndef DISPLAY_H
#define DISPLAY_H
#include "sprite.h"
#include "colors.h"
#include "monster.h"
#include "geometry.h"
#include "tower.h"
#include "game.h"
#include "installation.h"
#define PI 3.14

int display_map(GLuint* texture);
void display_right_column();
void draw_perim(float rayon);
int display_path(Map* map);
int display_money(GLuint* texture);
int display_full(GLuint* texture);
int display_monster(Monster* m, SDL_Surface* img, GLuint texture);
int display_wave(List_Monster *l_monster);
int display_tower(Tower* current, SDL_Surface* tourImg, GLuint *tourTexture);
int display_list_tower(List_Tower* list_tower);
int display_range_tower(Tower* t);
int display_installation(Installation* i, SDL_Surface* instImg, GLuint *instTexture);
int display_list_installation(List_Installation* list_inst);
void drawCircle (int fill, int nbSeg);
int tower_on_building(List_Tower* list_tower, float x, float y, List_Installation* list_inst);
int inst_on_building(List_Installation* list_inst, float x, float y, List_Tower* list_tower);

int check_around_tower(Tower* t, List_Installation* list_inst);
void update_tower(Tower* t, InstallationType);
int check_around_inst(Installation* i, List_Tower* list_tower);
int click_delete_tower(List_Tower* l_tower, Tower* current, Game* game, float x, float y);
int click_installation_delete(List_Installation* l_inst, Installation* current, Game* game, float x, float y);

int shot_monster(Monster* m, Tower* t);
int display_cross(GLuint* texture);
Monster_Type monster_on_tower(List_Monster* list_monster, List_Tower* list_tower);
void displayTowerFeatures(Tower* t);
Tower* constructTowerSelected(List_Tower* l_tower, int x, int y);

#endif

#ifndef SPRITE_H
#define SPRITE_H

#include "map.h"
#include "image.h"

int is_loaded(SDL_Surface *image);
void drawQuad(GLuint texture);
SDL_Surface* load_map_texture(Map* map, GLuint *texture);
SDL_Surface* load_sprite(char* file_name, GLuint *texture);
void free_sprite(GLuint texture, SDL_Surface* img);
//int draw_monster(GLuint monster);
void drawSquare(GLuint *monster);
#endif
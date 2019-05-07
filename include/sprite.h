#ifndef SPRITE_H
#define SPRITE_H

#include "map.h"
#include "image.h"

int is_loaded(SDL_Surface *image);
void drawQuad(GLuint texture);
SDL_Surface* load_map_texture(Map* map, GLuint *texture);
int load_sprite(char* file_name, GLuint texture, SDL_Surface* img);
void free_sprite(GLuint texture, SDL_Surface* img);
int draw_map(GLuint* texture);
#endif
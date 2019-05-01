#ifndef SPRITE_H
#define SPRITE_H

#include "map.h"
#include "image.h"

int is_loaded(SDL_Surface *image);
int load_map_texture(Map* map, GLuint texture, SDL_Surface* image);
int load_sprite(char* file_name, GLuint texture, SDL_Surface* img);
void free_sprite(GLuint texture, SDL_Surface* img);

#endif
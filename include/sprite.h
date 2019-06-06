#ifndef SPRITE_H
#define SPRITE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "map.h"
#include "image.h"

// Check if image loaded
int is_loaded(SDL_Surface *image);
// Draw quadrilatere
void drawQuad(GLuint texture);
// Load map texture
SDL_Surface* load_map_texture(Map* map, GLuint *texture);
// Load sprite
SDL_Surface* load_sprite(char* file_name, GLuint *texture);
// Free sprite
void free_sprite(GLuint texture, SDL_Surface* img);

#endif
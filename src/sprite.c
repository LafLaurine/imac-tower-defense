#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/sprite.h"

//check si image bien chargée
int is_loaded(SDL_Surface *image)
{
    if(image == NULL) {
        printf("%s\n", "Image not loaded");
        SDL_Quit();
        return 0;
    }
    printf("%s\n", "Image loaded");
    return 1;
}


//charge texture map

int load_map_texture(Map* map, GLuint texture, SDL_Surface* image) {
	image = IMG_Load(map->img->path);
	is_loaded(image);
	glGenTextures(1, &texture);
	//lier la texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//choisi le bon format selon l'image
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(
    GL_TEXTURE_2D,
    0, 
    GL_RGB,
    image->w,
    image->h, 
    0, 
    GL_RGB,
    GL_UNSIGNED_BYTE, 
    image->pixels);
	return 1;
}

//charger sprite

int load_sprite(char* file_name, GLuint texture, SDL_Surface* img) {
	
	img = IMG_Load(file_name);
	is_loaded(img);
	glGenTextures(1,&texture);
	//dire qu'on fait des modification sur cette texture
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D(
    GL_TEXTURE_2D,
    0, 
    GL_RGB,
    img->w,
    img->h, 
    0, 
    GL_RGB,
    GL_UNSIGNED_BYTE, 
    img->pixels);
	return 1;
}

void free_sprite(GLuint texture, SDL_Surface* img) { 
	SDL_FreeSurface(img);
    glBindTexture(GL_TEXTURE_2D,0);
}

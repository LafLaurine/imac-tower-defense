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
    return 1;
}

void drawQuad(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);        
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex2f(-0.5,-0.5);
            glTexCoord2f(0, 0);
            glVertex2f(-0.5,0.5);
            glTexCoord2f(1, 0);
            glVertex2f(0.5,0.5);
            glTexCoord2f(1, 1);
            glVertex2f(0.5,-0.5);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
    
//charge texture map
SDL_Surface* load_map_texture(Map* map, GLuint *texture) {
    SDL_Surface *image = IMG_Load(map->img->path);

    is_loaded(image);

    glGenTextures(1,texture);
    glBindTexture(GL_TEXTURE_2D,*texture);
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

    SDL_FreeSurface(image);
    glBindTexture(GL_TEXTURE_2D,0);
    return image;
}

//charger sprite

SDL_Surface* load_sprite(char* file_name, GLuint *texture) {
    SDL_Surface *image = IMG_Load(file_name);
    is_loaded(image);
    glGenTextures(1,texture);
    glBindTexture(GL_TEXTURE_2D,*texture);
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

    SDL_FreeSurface(image);
    glBindTexture(GL_TEXTURE_2D,0);
    return image;
}

void free_sprite(GLuint texture, SDL_Surface* img) { 
    SDL_FreeSurface(img);
    glBindTexture(GL_TEXTURE_2D,0);
}
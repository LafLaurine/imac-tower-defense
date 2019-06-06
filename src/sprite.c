#include "../include/sprite.h"

int is_loaded(SDL_Surface *image) {
    if(image == NULL) {
        printf("Image not loaded");
        SDL_Quit();
        return 0;
    }
    return 1;
}

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

SDL_Surface* load_sprite(char* file_name, GLuint *texture) {
    SDL_Surface *image = IMG_Load(file_name);
    is_loaded(image);
    glGenTextures(1,texture);
    glBindTexture(GL_TEXTURE_2D,*texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    GLenum format;
    switch(image->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            printf("Format des pixels de l’image non pris en charge\n");
            exit(EXIT_FAILURE);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
    SDL_FreeSurface(image);
    glBindTexture(GL_TEXTURE_2D,0);
    return image;
}

void free_sprite(GLuint texture, SDL_Surface* img) { 
    SDL_FreeSurface(img);
    glBindTexture(GL_TEXTURE_2D,0);
}
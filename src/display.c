#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/display.h"

void draw_circle(float rayon) 
{
	
	int i, j = 100;
	float angle, x1, y1;
	
	glBegin(GL_LINE_STRIP);

	for(i = 0; i <= j; i++) {
		angle = (2*3.14*i)/j;
		x1 = rayon*(cos(angle));
		y1 = rayon*(sin(angle));
		glVertex2f(x1,y1);
	}

	glEnd();

}

void draw_rectangle(int x1, int y1, int x2, int y2) 
{
	glBegin(GL_QUADS);
		glVertex2f(x1,y1);
		glVertex2f(x2,y1);
		glVertex2f(x2,y2);
		glVertex2f(x1,y2);
	glEnd();
}

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

int load_map(Map* map, GLuint* texture, SDL_Surface* image) {
	image = IMG_Load(map->img->path);
	is_loaded(image);
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	return 1;
}

void free_display(GLuint* texture, SDL_Surface* img) {
	SDL_FreeSurface(img);
	glDeleteTextures(1, texture);
}
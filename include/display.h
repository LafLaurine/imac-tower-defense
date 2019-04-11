#ifndef DISPLAY_H
#define DISPLAY_H

void draw_circle(float rayon);
void draw_rectangle(int x1, int y1, int x2, int y2);
int load_map(Map* map, GLuint* texture, SDL_Surface* image);
void free_display(GLuint* texture, SDL_Surface* img);

#endif
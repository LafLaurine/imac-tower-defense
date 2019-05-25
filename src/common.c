#include <stdlib.h>
#include <stdio.h>
#include "../include/common.h"

int is_intersect(float x1, float y1, float x2, float y2, float radius){
	float distanceSquare = (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
	return distanceSquare < radius*radius*4;
}

int square_intersect_circle(float x1, float x2, float y1, float y2, int size_1, int size_2){
    if(x1 + (size_1 + size_2) >= x2 && x1 - (size_1 + size_2) <= x2 && y1 + (size_1 + size_2) >= y2 && y1 - (size_1 + size_2) <= y2){
        return 1;
    }else{
        return 0;
    }
}

int square_intersect_square(float x1, float x2, float y1, float y2, int size_1, int size_2){
    if(x1 + (size_1 + size_2) >= x2 && x1 - (size_1 + size_2) <= x2 && y1 + (size_1 + size_2) >= y2 && y1 - (size_1 + size_2) <= y2){
        return 1;
    }else{
        return 0;
    }
}

void initFont(TTF_Font* font, SDL_Surface* texte) {
    font = loadFont(FONT,24);
    SDL_Color white = {255, 255, 255};
    texte = TTF_RenderText_Blended(font, "Appuyez sur h pour obtenir de l'aide !",white);
}

TTF_Font* loadFont(const char* fontName, int size) {
    char fontPath[80] = "fonts/";
    strcat(fontPath, fontName);
    strcat(fontPath, ".TTF");

    TTF_Font* font = TTF_OpenFont(fontPath, size);

    if(!font) {
        fprintf(stderr, "TTF: %s\n", TTF_GetError());
        exit (EXIT_FAILURE);
    }

    return font;
}

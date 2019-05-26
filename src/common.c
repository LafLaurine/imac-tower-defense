#include <stdlib.h>
#include <stdio.h>
#include "../include/common.h"

TTF_Font *fonts[MAX_FONTS];


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

void init_text()
{
	TTF_Font* font = TTF_OpenFont("bitmap.TTF", 24);
	if(font == NULL)
	{
		fprintf(stderr,"Erreur au chargement de la police");
		exit(-1);
	}
	fonts[FONT_24] = font;
	fonts[FONT_32] = TTF_OpenFont("bitmap.TTF", 32);
	fonts[FONT_48] = TTF_OpenFont("bitmap.TTF", 48);
}

void free_text()
{
	int i;
	for(i = 0; i<MAX_FONTS; i++)
	{
		TTF_CloseFont(fonts[i]);
	}
}

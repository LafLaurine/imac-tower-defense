#include <stdio.h>
#include <stdlib.h>
#include "../include/colors.h"

Color3f createColor(unsigned char r, unsigned char g, unsigned char b){
    Color3f couleur;

    couleur.r = r;
    couleur.g = g;
    couleur.b = b;

    return couleur;
}
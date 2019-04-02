#include <stdio.h>
#include <stdlib.h>
#include "../include/colors.h"

Color3f createColor(float r, float g, float b){
    Color3f couleur;

    couleur.r = r;
    couleur.g = g;
    couleur.b = b;

    return couleur;
}

Color3f addColors(Color3f c1, Color3f c2){
    Color3f couleur;

    couleur.r = c1.r + c2.r;
    couleur.g = c1.g + c2.g;
    couleur.b = c1.b + c2.b;

    return couleur;
}

Color3f subColors(Color3f c1, Color3f c2){
    Color3f couleur;

    couleur.r = c1.r - c2.r;
    couleur.g = c1.g - c2.g;
    couleur.b = c1.b - c2.b;

    return couleur;
}

Color3f multColors(Color3f c1, Color3f c2){
    Color3f couleur;

    couleur.r = c1.r * c2.r;
    couleur.g = c1.g * c2.g;
    couleur.b = c1.b * c2.b;

    return couleur;
}

Color3f multColor(Color3f c, float a){
    Color3f couleur;

    couleur.r = c.r * a;
    couleur.g = c.g * a;
    couleur.b = c.b * a;

    return couleur;
}

Color3f divColor(Color3f c, float a){
    Color3f couleur;

    couleur.r = c.r / a;
    couleur.g = c.g / a;
    couleur.b = c.b / a;

    return couleur;
}
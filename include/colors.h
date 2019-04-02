#ifndef COLORS_H__
#define COLORS_H__

typedef struct col3f {
    float r, g, b;
} Color3f;


// Construit la couleur (r, g, b)
Color3f createColor(float r, float g, float b);

// Addition, soustraction et multiplication des couleurs C1 et C2
Color3f addColors(Color3f c1, Color3f c2);
Color3f subColors(Color3f c1, Color3f c2);
Color3f multColors(Color3f c1, Color3f c2);

// Multiplication et division d'un couleur C par un scalaire a
Color3f multColor(Color3f c, float a);
Color3f divColor(Color3f c, float a);

#endif
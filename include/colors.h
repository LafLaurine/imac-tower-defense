#ifndef COLORS_H__
#define COLORS_H__

typedef struct col3f {
    unsigned char r, g, b;
} Color3f;


// Construit la couleur (r, g, b)
Color3f createColor(unsigned char r, unsigned char g, unsigned char b);
#endif
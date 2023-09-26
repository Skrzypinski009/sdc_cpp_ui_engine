#pragma once 

#include <SDL2/SDL_stdinc.h>

typedef struct Color{
    Uint8 r, g, b, a;
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color();
    static Color zero();
} Color;

#include "../include/color.h"
#include <SDL2/SDL_stdinc.h>

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a):
    r(r), g(g), b(b), a(a) {}

Color::Color(){
    r=0; g=0; b=0; a=255;
}

Color Color::zero(){
    return Color(0,0,0,0);
}
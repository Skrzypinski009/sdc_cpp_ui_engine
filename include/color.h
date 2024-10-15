#pragma once 

#include "SDL.h"

class Color{
public:
    Uint8 r, g, b, a;
    static const Color TRANSPARENT;
    static const Color BLACK;
    static const Color WHITE;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color CYAN;
    static const Color MAGENTA;

    Color();
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Color(Color* other);
    Color(const char* hex);

    void setColor(const Color color);
};

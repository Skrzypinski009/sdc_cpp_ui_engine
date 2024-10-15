#pragma once

#include "SDL.h"

#include "veci2.h"
#include "color.h"

class RectStyle{
    SDL_Rect rect;
public:
    Color background_color;
    Color border_color;

    RectStyle(Color background_color, Color border_color);
    void draw(SDL_Renderer *renderer, Veci2 position, Veci2 size);
};
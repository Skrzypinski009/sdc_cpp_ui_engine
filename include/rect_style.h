#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>

#include "veci2.h"

class RectStyle{
    SDL_Rect rect;
public:
    SDL_Color background_color;
    SDL_Color border_color;

    RectStyle(SDL_Color background_color, SDL_Color border_color);
    void draw(SDL_Renderer *renderer, Veci2 position, Veci2 size);
};
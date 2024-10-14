#include "rect_style.h"

#include "SDL.h"

RectStyle::RectStyle(SDL_Color background_color, SDL_Color border_color) {
    this->background_color = background_color;
    this->border_color = border_color;
}

void RectStyle::draw(SDL_Renderer *renderer, Veci2 position, Veci2 size){
    if(background_color.a > 0){
        rect = {position.x, position.y, size.x, size.y};
        // std::cout<<"position: {"<<position.x<<", "<<position.y<<"}\n";
        // std::cout<<"size: {"<<size.x<<", "<<size.y<<"}\n";
        // std::cout<<"rect: {"<<position.x<<", "<<position.y<<", "<<size.x<<", "<<size.y<<"}\n";
        // std::cout<<"background color: {"<<(int)background_color.r<<", "<<(int)background_color.g<<", "<<(int)background_color.b<<", "<<(int)background_color.a<<"}\n";
        // std::cout<<"border color: {"<<(int)border_color.r<<", "<<(int)border_color.g<<", "<<(int)border_color.b<<", "<<(int)border_color.a<<"}\n";
        SDL_SetRenderDrawColor(
            renderer, 
            background_color.r, background_color.g, 
            background_color.b, background_color.a
        );
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(
            renderer, 
            border_color.r, border_color.g, 
            border_color.b, border_color.a
        );
        SDL_RenderDrawRect(renderer, &rect);
        
    }
}
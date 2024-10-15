#include "label.h"

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "object.h"
#include "veci2.h"


Label::Label(
    const std::string text_, 
    const std::string font_path_,
    const std::size_t font_size_,
    const SDL_Color color_,
    const bool wrapped_
) : Object({0,0}, {100, 100}, type=ObjectType::LABEL) {
    text = text_;
    font_path = font_path_;
    font_size = font_size_;
    color = color_;
    wrapped = wrapped_;
}

Label::Label() : Object({0,0}, {100, 100}, type=ObjectType::LABEL) {
    text = "";
    font_size = 20;
    color = {255,255,255};
    wrapped = false;
    //no font path
}

Label::~Label(){
    TTF_CloseFont(text_font);
}

void Label::setText(const std::string text_){
    text = text_;
}

std::string Label::getText() const {
    return text;
}

void Label::setFontPath(const std::string font_path_){
    font_path = font_path_;
}

std::string Label::getFontPath() const {
    return font_path;
}

void Label::setFontSize(const std::size_t font_size_){
    font_size = font_size_;
}

std::size_t Label::getFontSize() const {
    return font_size;
}

void Label::setColor(const SDL_Color color_){
    color = color_;
}

SDL_Color Label::getColor() const {
    return color;
}

void Label::setWrapped(const bool wrapped_){
    wrapped = wrapped_;
}

bool Label::getWrapped() const {
    return wrapped;
}

void Label::loadFont(){
    text_font = TTF_OpenFont(font_path.c_str(), font_size);
    if(!text_font){
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

void Label::draw(SDL_Renderer *renderer){
    // std::cout<<"drawing label"<<std::endl;
    if(getRectStyle())
        getRectStyle()->draw(renderer, getGlobalPosition(), getSize());

    if(!text_font){
        std::cout << "Font is not loaded!\n";
        return;
    }
    SDL_Surface *text_surface;

    if(wrapped)
        text_surface = TTF_RenderText_Blended_Wrapped(text_font, text.c_str(), color, getSize().x);
    else
        text_surface = TTF_RenderText_Blended(text_font, text.c_str(), color);

    if(!text_surface){
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    SDL_Rect rect = {getGlobalPosition().x, getGlobalPosition().y, text_surface->w, text_surface->h};
    SDL_Rect clip_rect = getClipRect();
    SDL_RenderSetClipRect(renderer, &clip_rect);
    SDL_RenderCopy(renderer, text_texture, NULL, &rect);
    SDL_RenderSetClipRect(renderer, NULL);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}


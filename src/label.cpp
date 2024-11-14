#include "label.h"

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "object.h"
#include "veci2.h"
#include "log.h"


Label::Label(SDL_Renderer *renderer_, const std::string text_, const std::string& style_name_
) : Object({0,0}, {100, 100}, type=ObjectType::LABEL) {
    renderer = renderer_;
    setStyle(style_name_);
    setText(text_);
}

Label::Label() : Object({0,0}, {200, 30}, type=ObjectType::LABEL) {
    renderer = nullptr;
    text = "";
    setStyle("text_default");
}

Label::~Label(){
    TTF_CloseFont(text_font);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void Label::setText(const std::string text_){
    text = text_;
    createTexture();
}

void Label::setSize(Vec2 size_){
    Object::setSize(size_);
    createTexture();
}

std::string Label::getText() const {
    return text;
}
void Label::draw(SDL_Renderer *renderer_){
    Object::draw(renderer);

    SDL_Rect rect = {(int)getGlobalPosition().x, (int)getGlobalPosition().y, text_surface->w, text_surface->h};
    SDL_Rect clip_rect = getClipRect();
    if (style == nullptr) return;
    style->drawText(renderer, text_texture, &rect, &clip_rect);

}

void Label::createTexture()
{
    if (style == nullptr) return;
    style->createTextTexture(renderer, (int)getSize().x, text, &text_font, &text_texture, &text_surface, "");
    if (style->get("text_clip") == "false"){
        if (style->get("text_wrap") == "true"){
            size = (Vec2(getSize().x, (float)text_surface->h));
            return;
        }
        float y = (float)text_surface->h;
        if (getSize().y > y) y = getSize().y;
        size = (Vec2((float)text_surface->w, y));
        return;
    }
}
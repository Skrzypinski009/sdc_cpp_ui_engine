#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include "object.h"



class Label : public Object{
    std::string text;
    // std::string font_path;
    // std::size_t font_size;
    // SDL_Color color;
    // bool wrapped;

    TTF_Font *text_font;
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Renderer* renderer;
public:
    
    Label(SDL_Renderer* renderer_, const std::string text_ , const std::string& style_name_
        // const std::string font_path_,
        // const std::size_t font_size_,
        // const SDL_Color color_,
        // const bool wrapped_
    );
    Label();
    ~Label();

    void setText(const std::string text_);
    std::string getText() const;
    // void setFontPath(const std::string font_path_);
    // std::string getFontPath() const;
    // void setFontSize(const std::size_t);
    void setSize(Vec2 size_) override;

    // std::size_t getFontSize() const;
    // void setColor(const SDL_Color color_);
    // SDL_Color getColor() const;
    // void setWrapped(const bool wrapped_);
    // bool getWrapped() const;

    // void loadFont();
    void createTexture();
    virtual void draw(SDL_Renderer *renderer_) override;
}; 

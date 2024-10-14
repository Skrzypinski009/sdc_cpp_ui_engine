#pragma once

#include "object.h"

#include "SDL.h"
#include "SDL_ttf.h"


class Label : public Object{
    TTF_Font *text_font;
    std::string text;
    std::string font_path;
    size_t font_size;
    SDL_Color color;
    bool wrapped;
public:
    
    Label(
        const std::string text_, 
        const std::string font_path_,
        const size_t font_size_,
        const SDL_Color color_,
        const bool wrapped_
    );
    Label();
    ~Label();

    void setText(const std::string text_);
    std::string getText() const;
    void setFontPath(const std::string font_path_);
    std::string getFontPath() const;
    void setFontSize(const size_t);
    size_t getFontSize() const;
    void setColor(const SDL_Color color_);
    SDL_Color getColor() const;
    void setWrapped(const bool wrapped_);
    bool getWrapped() const;

    void loadFont();
    void createTexture();
    virtual void draw(SDL_Renderer *renderer) override;
}; 

#pragma once

#include <map>
#include <string>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"

struct Style{
    std::map<std::string, std::string> options;
    
    Style();
    Style(std::map<std::string, std::string> options);

    void addOption(const std::string& name, const std::string& value, const std::string& sufix = "");
    // addOption -> void set(const std::string& name, const std::string& value, const std::string& sufix = "");
    std::string get(const std::string& name, const std::string& sufix = "") const;
    std::string getAlt(const std::string& name, const std::string& sufix = "") const;
    // bool hasOption(const std::string& name, const std::string& sufix = "") const;
    bool has(const std::string& name, const std::string& sufix = "") const;
    bool hasAlt(const std::string& name, const std::string& sufix = "") const;

    // RECT
    void drawBackground(SDL_Renderer* renderer, SDL_Rect* rect, std::string option_sufix = "") const;

    void drawBorder(SDL_Renderer* renderer, SDL_Rect* rect, std::string option_sufix = "") const;

    void drawRect(SDL_Renderer* renderer, SDL_Rect* rect, std::string option_sufix = "") const;

    // FONT 
    void createTextTexture(SDL_Renderer* renderer, const std::size_t width, const std::string& text,
    TTF_Font** text_font, SDL_Texture** text_texture, SDL_Surface** text_surface,
    std::string option_suffix) const;

    void drawText(SDL_Renderer* renderer, SDL_Texture* text_texture, SDL_Rect* rect, SDL_Rect* clip_rect) const;
};
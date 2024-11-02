#pragma once

#include <map>
#include <string>
#include <vector>

#include "SDL.h"

struct Style{
    std::map<std::string, std::string> options;
    
    Style();
    Style(std::map<std::string, std::string> options);
    void addOption(const std::string& name, const std::string& value);
    std::string get(const std::string& name) const;
    bool hasOption(const std::string& name) const;
    void drawBackground(SDL_Renderer* renderer, const std::string& option_name, SDL_Rect* rect) const;
    void drawBorder(SDL_Renderer* renderer, const std::string& option_name, SDL_Rect* rect) const;
};
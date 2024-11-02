#include "style.h"

#include <map>
#include <string>

#include "SDL.h"

#include "color.h"

Style::Style()
{
    options = {};
}

Style::Style(std::map<std::string, std::string> options) : options(options) {}

void Style::addOption(const std::string& name, const std::string& value)
{
    options[name] = value;
}

std::string Style::get(const std::string& name) const
{
    return options.at(name);
}

bool Style::hasOption(const std::string& name) const
{
    return options.find(name) != options.end();
}

void Style::drawBackground(SDL_Renderer* renderer, const std::string& option_name, SDL_Rect* rect) const
{
    if(hasOption(option_name)){
        Color color(get(option_name).c_str());
        SDL_SetRenderDrawColor( renderer, 
            color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, rect);
    }
}

void Style::drawBorder(SDL_Renderer* renderer, const std::string& option_name, SDL_Rect* rect) const
{
    if(hasOption(option_name)){
        Color color(get(option_name).c_str());
        SDL_SetRenderDrawColor( renderer, 
            color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, rect);
    }
}
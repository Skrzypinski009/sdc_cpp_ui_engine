#include "style.h"

#include <map>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"

#include "color.h"
#include "log.h"

Style::Style()
{
    options = {};
}

Style::Style(std::map<std::string, std::string> options) : options(options) {}

void Style::addOption(const std::string& name, const std::string& value, const std::string& sufix)
{
    if (!sufix.empty()) {options[name + ":" + sufix] = value; return;}
    options[name] = value;
}

std::string Style::get(const std::string& name, const std::string& sufix) const
{
    if (!sufix.empty()) return options.at(name + ":" + sufix);
    return options.at(name);
}

std::string Style::getAlt(const std::string& name, const std::string& sufix) const
{
    if (!sufix.empty() && has(name, sufix)) return options.at(name + ":" + sufix);
    return options.at(name);
}

bool Style::has(const std::string& name, const std::string& sufix) const
{
    if (!sufix.empty()) return options.find(name + ":" + sufix) != options.end();
    return options.find(name) != options.end();
}

bool Style::hasAlt(const std::string& name, const std::string& sufix) const
{
    if (!sufix.empty() && options.find(name + ":" + sufix) != options.end()) return true;
    return options.find(name) != options.end();
}

void Style::drawRect(SDL_Renderer* renderer, SDL_Rect* rect, std::string option_sufix) const
{
    drawBackground(renderer, rect, option_sufix);
    drawBorder(renderer, rect, option_sufix);
}

void Style::drawBackground(SDL_Renderer* renderer, SDL_Rect* rect, std::string option_sufix) const
{
    if (!hasAlt("background_color", option_sufix)) return;
    Color color( getAlt("background_color", option_sufix).c_str() );
    SDL_SetRenderDrawColor( renderer, 
        color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, rect);
}

void Style::drawBorder(SDL_Renderer* renderer, SDL_Rect* rect, std::string option_sufix) const
{
    if (!hasAlt("border_color", option_sufix)) return;

    Color color(getAlt("border_color", option_sufix).c_str());
    SDL_SetRenderDrawColor( renderer, 
        color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, rect);
}

void Style::createTextTexture(SDL_Renderer* renderer, const std::size_t width, const std::string& text,
    TTF_Font** text_font, SDL_Texture** text_texture, SDL_Surface** text_surface,
    std::string option_sufix) const
{
    if (!hasAlt("font_path", option_sufix) || !hasAlt("font_size", option_sufix)) return;
    *text_font = TTF_OpenFont(getAlt("font_path", option_sufix).c_str(), atoi(getAlt("font_size", option_sufix).c_str()) );
    if(!*text_font)
        Log::error((std::string("Failed to load font: ") + SDL_GetError()).c_str());

    if (!hasAlt("text_color", option_sufix)) return;
    Color text_color = Color(getAlt("text_color", option_sufix).c_str());
    SDL_Color color = { text_color.r, text_color.g, text_color.b, text_color.a };

    if (*text_surface != nullptr)
        SDL_FreeSurface(*text_surface);
    if (*text_texture != nullptr)
        SDL_DestroyTexture(*text_texture);

    if(hasAlt("text_wrap", option_sufix) && getAlt("text_wrap", option_sufix) == "true")
        *text_surface = TTF_RenderText_Blended_Wrapped(*text_font, text.c_str(), color, width);
    else
        *text_surface = TTF_RenderText_Blended(*text_font, text.c_str(), color);

    if(!*text_surface)
        Log::error((std::string("Failed to render text: ") + SDL_GetError()).c_str());

    *text_texture = SDL_CreateTextureFromSurface( renderer, *text_surface );
}

void Style::drawText(SDL_Renderer* renderer, SDL_Texture* text_texture, SDL_Rect* rect, SDL_Rect* clip_rect) const
{
    if (text_texture == nullptr){
        Log::warning("Text texture is null");
        return;
    }
    if (hasAlt("text_clip") && getAlt("text_clip") == "true")
        SDL_RenderSetClipRect(renderer, clip_rect);
    SDL_RenderCopy(renderer, text_texture, NULL, rect);
    SDL_RenderSetClipRect(renderer, NULL);
}
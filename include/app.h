#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_rect.h>
#include <SDL_ttf.h>

#include "object.h"
#include "container.h"
#include "button.h"
#include "event_manager.h"
#include "rect_style.h"

#include <iostream>
#include <vector>


struct App{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Object* root_obj;
    EventManager event_manager;
    std::vector<RectStyle*> styles;

    App();

    void start();
    void stop();
    void loop();
    void draw();
    void setRootObject(Object* obj);
    void updateRootObject();
    void deleteObject(Object *obj);
    void register_style(RectStyle *rect_style);
    void delete_styles();
};

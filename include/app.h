#pragma once

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"

#include "object.h"
#include "container.h"
#include "button.h"
#include "event_manager.h"
#include "rect_style.h"
#include "veci2.h"

struct App{
    SDL_Window *window;
    SDL_Renderer *renderer;
    Object* root_obj;
    EventManager event_manager;
    std::vector<RectStyle*> styles;
    Veci2 window_size;

    App(Veci2 windows_size_);

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
